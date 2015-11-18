if (!bench.chart) bench.chart = {};

bench.chart.bubbleChart = function() {
    var width = 600;
    var height = 600;
    var padding = 30;
    var dispatch = d3.dispatch("select");
    var data, scalars;
    var svg, selector, graph;

    function chart(container) {

        scalars = data[0].scalars;
        selector = bench.chart
            .selector(d3.values(scalars).map(function(d){return d.name;}))
            .on("select", function(idx) { update(); });
        selector(container);
        selector.selected(d3.keys(scalars).indexOf("test.iterations"));

        svg = container.append("svg")
            .classed("bubble-chart", true)
            .attr({
                width: width,
                height: height
            });

        graph = svg.append("g")
            .classed("graph", true)
            .attr("transform", "translate("+padding+")");

        svg.append("g")
            .classed("axis", true)
            .classed("bottom-axis", true)
            .attr("transform", "translate("+padding+","+(height-padding)+")");

        svg.append("g")
            .classed("axis", true)
            .classed("left-axis", true)
            .attr("transform", "translate("+padding+",0)")

        update();
    }

    function update() {
        var getValue, getText;

        var key = d3.keys(scalars)[selector.selected()];

        if (key != undefined) {
            var unit = bench.units[scalars[key].unit];
            selector.text(selector.selected(), scalars[key].name);
            getValue = function(test) { return key in test.scalars ? test.scalars[key].value : NaN; }
            getText = function(test) { return test.error ? test.error : unit(getValue(test)); }
        } else {
            getValue = function(test) {return NaN;}
            getText = function(test) { return test.error ? test.error : "No Data"; }
        }

        var sizeValues = bench.computations.getContentSizes(data);
        var threadsValues = bench.computations.getThreadCounts(data);

        var maxDiameter = d3.min([(width-padding*2) / sizeValues.length, (height-padding*2) / threadsValues.length]) - 2;
        var maxRadius = maxDiameter / 2;

        var sizeScale = d3.scale.ordinal().domain(sizeValues).rangePoints([maxRadius+padding,width-maxRadius-padding]);
        var threadsScale = d3.scale.ordinal().domain(threadsValues).rangePoints([maxRadius+padding,height-maxRadius-padding]);

        var valueScale = d3.scale.log()
            .domain(d3.extent(data, getValue))
            .range([30,maxDiameter]);

        var bubbles = graph
            .selectAll("circle")
            .classed("bubble", true)
            .data(data);

        var getBubbleRadius = function(test) {
            return valueScale(getValue(test))/2 || maxDiameter/4;
        }

        bubbles
            .classed("error", function(d) {return !!d.error})
            .transition()
            .attr("r", getBubbleRadius)

        bubbles
            .enter()
            .append("circle")
            .classed("bubble", true)
            .attr({
                "cx": function(d) { return sizeScale(d.content_size) },
                "cy": function(d) { return threadsScale(d.thread_count) },
                "r": getBubbleRadius
            })
            .classed("error", function(d) {return !!d.error})
            .on("click", function(d) {
                graph.selectAll("circle").classed("selected", false);
                d3.select(this).classed("selected", true);
                dispatch.select(d.id);
            });

        bubbles
            .exit()
            .remove();

        var labels = graph
            .selectAll("text")
            .data(data);

        labels
            .enter()
            .append("text")
            .attr({
                "x": function(d) { return sizeScale(d.content_size) },
                "y": function(d) { return threadsScale(d.thread_count) },
                "text-anchor": "middle",
                "dominant-baseline": "central",
                "pointer-events": "none"
            });

        labels
            .attr("opacity",0)
            .attr("font-size", function(d) {return getBubbleRadius(d)/2.5 + "px"})
            .text(getText)
            .transition()
            .attr("opacity",1)

        var sizeAxis = d3.svg.axis().scale(sizeScale).orient("bottom").tickFormat(function(d) { return bench.units.bytes(d); });
        svg.select("g.bottom-axis").call(sizeAxis);

        var threadsAxis = d3.svg.axis().scale(threadsScale).orient("left").tickFormat(function(d) { return d + "t"; });
        svg.select("g.left-axis").call(threadsAxis);
    }

    chart.data = function(value) {
        data = value;
    }
    return d3.rebind(chart, dispatch, "on");
};
