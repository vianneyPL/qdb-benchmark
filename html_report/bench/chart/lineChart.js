if (!bench.chart) bench.chart = {};

bench.chart.lineChart = function() {
    var width = 600;
    var height = 600;
    var leftPadding = 80;
    var rightPadding = 80;
    var padding = 30;
    var data;
    var svg, selector;
    var stacked = false;
    var stackLabel;

    var headerHeight = 30;
    var headerWidth = 300;

    function chart(container) {     
        selector = bench.chart
            .selector(d3.values(data.series).map(function(d){return d.name}))
            .on("select", function(idx) { update(); });
        selector(container);
        selector.selected(d3.keys(data.series).indexOf("test.iterations"));

        stackLabel = container.append("label").text("Stacked");
        stackLabel.append("input")
            .attr("type", "checkbox")
            .on("change", function() {
                stacked = this.checked;
                update();
            });

        svg = container.append("svg")
            .classed("line-chart", true)
            .attr({
                "viewBox": "0 0 "+width+" "+height,
                "preserveAspectRatio": "xMinYMin meet"
            });

        svg.append("g").classed("graph", true).attr("transform", "translate("+leftPadding+")");
        svg.append("g").classed("axis", true).classed("x-axis", true).attr("transform", "translate("+leftPadding+","+(height-padding)+")");
        svg.append("g").classed("axis", true).classed("left-axis", true).attr("transform", "translate("+leftPadding+")");

        update();
    }

    function makeLines(samples) {
        var lines = [];
        for (var sampleIndex = 0; sampleIndex < samples.length; sampleIndex++) {
            var time = samples[sampleIndex][0];

            for (var lineIndex = 0; lineIndex < samples[0].length - 1 ; lineIndex++) {
                if (sampleIndex==0) lines[lineIndex] = [];

                var value = samples[sampleIndex][lineIndex+1];
                if (stacked && lineIndex > 0) value += lines[lineIndex-1][sampleIndex].value;

                value = lines[lineIndex].push({"time" : time, "value" : value});
            }
        }
        return lines;
    }

    chart.update = update;
    function update() {
        var serie = d3.values(data.series)[selector.selected()];
        selector.text(selector.selected(), serie.name);

        var unit = bench.units[serie.unit];

        var lines = makeLines(serie.samples);

        stackLabel.style("visibility", function(d) {
                return lines.length>1 ? "visible" : "hidden";
            });

        var timeMax = d3.max(lines[0], function(d){return d.time})

        var timeScale = d3.scale.linear()
            .domain([0, timeMax])
            .range([0, width-leftPadding-rightPadding]);

        var valueMax = d3.max(lines, function(points) {
            return d3.max(points, function(d) {
                return d.value;
            });
        });
        var valueMin = d3.min(lines, function(points) {
            return d3.min(points, function(d) {
                return d.value;
            });
        });

        if (valueMin == valueMax) {
            if (valueMin == 0) {
                valueMin = -0.001;
                valueMax = 0.001;
            } else {
                valueMin *= 0.9;
                valueMax *= 1.1;
            }
        }

        var valueScale = d3.scale.linear()
            .domain([valueMin, valueMax])
            .range([height-padding, 0]);

        var lineFunc = d3.svg.line()
            .x(function(d) { return timeScale(d.time); })
            .y(function(d) { return valueScale(d.value); })
            .interpolate("linear");

        var paths = svg.select(".graph")
            .selectAll("path")
            .classed("line", true)
            .data(lines);

        paths
            .transition()
            .attr("d", function(d) { return lineFunc(d); })

        paths
            .enter()
            .append("path")
            .classed("line", true)
            .attr("opacity", 0)
            .attr("d", function(d) { return lineFunc(d); })
            .transition()
            .attr("opacity", 1)

        paths
            .exit()
            .transition()
            .attr("opacity", 0)
            .remove();

        var timeAxis = d3.svg.axis().scale(timeScale).orient("bottom")
          .tickFormat(function(d) { return bench.units.millisecond(d); }) ;

        svg.selectAll(".x-axis").call(timeAxis);

        var valueAxis = d3.svg.axis().scale(valueScale).orient("left")
            .tickFormat(function(d) { return unit(d); })
        svg.selectAll(".left-axis").call(valueAxis);
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }

    return chart;
};
