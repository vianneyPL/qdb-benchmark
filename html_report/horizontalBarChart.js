if (!d3.chart) d3.chart = {};

d3.chart.horizontalBarChart = function() {

    var width = 600;
    var height = 600;
    var padding = 30; 
    var dispatch = d3.dispatch(chart, "select");
    var data;
    var svg, graph, header;
    var selectedSerie = 1;

    function chart(container) {

        header = container.append("div").classed("header", true);
        header.append("button").classed("left", true).on("click", function() {
            selectedSerie+=testSeries.length-1;
            update();
        });
        header.append("span");
        header.append("button").classed("right", true).on("click", function() {
            selectedSerie++;
            update();
        });

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

        var serie = testSeries[selectedSerie%testSeries.length];

        header.selectAll("span").text(serie.name);

        var points = data.map(function(test){
            return {
                id: test.id,
                threads: test.threads[0].length-1,
                size: test.content_size,
                value: serie.value(test)
            }});        

        var threadsValues = d3.set(points.map(function(d){return d.threads})).values();
        var valueExtent = d3.extent(points, function(d) {return d.value});
        console.log("valueExtent", valueExtent)

        var threadsScale = d3.scale.ordinal().domain(threadsValues).rangeBands([padding,height-padding], 0.5);
        var valueScale = d3.scale.linear().domain(valueExtent).range([padding,width-padding]);

        var bars = graph
            .selectAll("rect")
            .classed("bar", true)
            .data(points);

        bars
            .enter()
            .append("rect")
            .classed("bar", true)
            .attr({
                x: 0,
                y: function(d) { return threadsScale(d.threads) },
                height: threadsScale.rangeBand()
            })
            .on("click", function(d) {
                graph.selectAll("rect").classed("selected", false);
                d3.select(this).classed("selected", true);
                dispatch.select(d.id);
            });

        bars
            .transition()
            .attr("width", function(d) { return valueScale(d.value) });

        var labels = graph
            .selectAll("text")
            .data(points);

        labels
            .enter()
            .append("text")
            .attr({
                y: function(d) { return threadsScale(d.threads) +threadsScale.rangeBand() / 2  },
                "text-anchor": "end",
                "dominant-baseline": "central",
                "pointer-events": "none"
            });

        labels
            .text(function(d){
                return serie.unit(d.value)
            })
            .transition()
            .attr("x", function(d) {return valueScale(d.value) - 10})

        var threadsAxis = d3.svg.axis().scale(threadsScale).orient("left").tickFormat(function(d) { return d + "t"; });
        graph.selectAll(".left-axis").call(threadsAxis);
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }

    return d3.rebind(chart, dispatch, "on");
};
