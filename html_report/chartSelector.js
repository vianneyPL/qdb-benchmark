if (!d3.chart) d3.chart = {};

d3.chart.chartSelector = function() {
    var dispatch = d3.dispatch("select");
    var div, span;

    var chart = function(container) {
        div = container.append("div").classed("header", true);

        div
            .append("button")
            .classed("left", true)
            .text("<")
            .on("click", function() { dispatch.select(-1); });            
        span= div.append("span");
        div
            .append("button")
            .classed("right", true)
            .text(">")
            .on("click", function() { dispatch.select(1); });
    }

    chart.text = function(value) {        
        console.log(value);
        span.text(value);
        return chart;
    }

    return d3.rebind(chart, dispatch, "on");
}