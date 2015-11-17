if (!bench.chart) bench.chart = {};

bench.chart.horizontalBarChart = function() {
    var width = 600;
    var height = 600;
    var padding = 70;
    var dispatch = d3.dispatch("select");
    var data;
    var svg, graph, selector;

    function chart(container) {

        var names = d3.values(data[0].scalars).map(function(d){return d.name;});

        selector = bench.chart
            .selector(names)
            .on("select", function(idx) { update(); });
        selector(container);
        selector.selected(d3.keys(data[0].scalars).indexOf("test.iterations"));

        svg = container
            .append("svg")
            .classed("bar-chart", true)
            .classed("horizontal-bar-chart", true)
            .attr({
                width: width,
                height: height
            });

        graph = svg
            .append("g")
            .classed("graph", true)
            .attr("transform", "translate("+padding+")");

        svg
            .append("g")
            .classed("axis", true)
            .classed("left-axis", true)
            .attr("transform", "translate("+padding+",0)");

        update();
    }

    function update() {
        var key = d3.keys(data[0].scalars)[selector.selected()];
        var unit = bench.units[data[0].scalars[key].unit]
        selector.text(selector.selected(), data[0].scalars[key].name);

        var getValue = function (test) {
            return test.scalars[key].value;
        }

        var threadsScale = d3.scale.ordinal()
            .domain(bench.computations.getThreadCounts(data))
            .rangeBands([padding,height-padding], 0.5);

        var valueScale = d3.scale.linear()
            .domain(d3.extent(data, getValue))
            .range([padding,width-padding]);

        var bars = graph
            .selectAll("rect")
                .classed("bar", true)
                .data(data);

        bars.enter()
            .append("rect")
                .classed("bar", true)
                .attr({
                    "x": 0,
                    "y": function(d) { return threadsScale(d.thread_count) },
                    "height": threadsScale.rangeBand()
                })
                .on("click", function(d) {
                    graph.selectAll("rect").classed("selected", false);
                    d3.select(this).classed("selected", true);
                    dispatch.select(d.id);
                });

        bars
            .transition()
            .attr("width", function(d) {
                return valueScale(getValue(d))
            });

        var labels = graph
            .selectAll("text")
            .data(data);

        labels
            .enter()
            .append("text")
            .attr({
                "y": function(d) { return threadsScale(d.thread_count) +threadsScale.rangeBand() / 2  },
                "text-anchor": "end",
                "dominant-baseline": "central",
                "pointer-events": "none"
            });

        labels
            .text(function(d) { return unit(getValue(d)); })
            .transition()
            .attr("x", function(d) {return valueScale(getValue(d)) - 10})

        var threadsAxis = d3.svg.axis().scale(threadsScale).orient("left").tickFormat(function(d) { return d + "t"; });
        svg.selectAll(".left-axis").call(threadsAxis);
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }

    return d3.rebind(chart, dispatch, "on");
};
