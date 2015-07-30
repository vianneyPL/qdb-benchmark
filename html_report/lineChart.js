if (!d3.chart) d3.chart = {};


function getTestFrequency(test) {
    var lines = [];
    var serie = test.threads;
    for (var i=1; i<serie.length; i++)
    {
        var currentSample = serie[i];
        var previousSample = serie[i-1];

        var elapsed = currentSample[0] - previousSample[0];
        if (elapsed<1) continue;

        for (var j=0;j<currentSample.length-1;j++)
        {
            if (lines[j] == undefined) lines[j] = [];

            var iterations = currentSample[j+1] - previousSample[j+1];

            lines[j].push({
                time: currentSample[0],
                speed: iterations*1000.0/elapsed
            });
        }
    }
    return lines;
}

function getTestThroughput(test) {
    var lines = getTestFrequency(test);
    lines.forEach(function(points){
        points.forEach(function(d){d.speed*=test.content_size})
    });
    return lines
}

function getTestMemory(test) {
    var lines = [];
    var serie = test.qdb_node_memory;
    for (var i=0; i<serie.length; i++)
    {
        var currentSample = serie[i];

        for (var j=0;j<currentSample.length-1;j++)
        {
            if (lines[j] == undefined) lines[j] = [];

            lines[j].push({
                time: currentSample[0],
                speed: currentSample[j+1]
            });
        }
    }
    return lines;
}

d3.chart.lineChart = function() {

    var width = 600;
    var height = 600;
    var leftPadding = 80; 
    var rightPadding = 80; 
    var padding = 30; 
    var data;
    var svg, header;

    var headerHeight = 30;
    var headerWidth = 300;
    var selectedSerie = 0;

    var series = [
        {
            "name": "Throughput",
            "unit": unit.byte_per_second,
            "lines": getTestThroughput
        },
        {
            "name": "Frequency",
            "unit": unit.hertz,
            "lines": getTestFrequency
        },
        {
            "name": "Memory usage",
            "unit": unit.byte,
            "lines": getTestMemory
        }];

    function chart(container) {

        header = d3.chart
            .chartSelector()
            .on("select", function(inc) {
                selectedSerie+=series.length+inc;
                update();
            });
        header(container);

        svg = container.append("svg")
            .classed("thread-chart", true)
            .attr({
                "viewBox": "0 0 "+width+" "+height,
                "preserveAspectRatio": "xMinYMin meet"
            });

        svg.append("g").classed("graph", true).attr("transform", "translate("+leftPadding+")");
        svg.append("g").classed("axis", true).classed("x-axis", true).attr("transform", "translate("+leftPadding+","+(height-padding)+")");
        svg.append("g").classed("axis", true).classed("left-axis", true).attr("transform", "translate("+leftPadding+")");

        update();
    }

    chart.update = update;
    function update() {      

        var serie = series[selectedSerie%series.length];
        header.text(serie.name);

        var lines = serie.lines(data);
        var timeMax = d3.max(lines[0], function(d){return d.time})

        var timeScale = d3.scale.linear()
            .domain([0, timeMax])
            .range([0, width-leftPadding-rightPadding]);

        var speedMax = d3.max(lines, function(points) {
            return d3.max(points, function(d) {
                return d.speed;
            });
        });
        var speedMin = d3.min(lines, function(points) {
            return d3.min(points, function(d) {
                return d.speed;
            });
        });
        var speedScale = d3.scale.linear()
            .domain([speedMin, speedMax])
            .range([height-padding, 0]);

        var lineFunc = d3.svg.line()
            .x(function(d) { return timeScale(d.time); })
            .y(function(d) { return speedScale(d.speed); })
            .interpolate("linear");

        var paths = svg.select(".graph")
            .selectAll("path")
            .classed("thread-speed", true)
            .data(lines)
            .attr("d", function(d) { return lineFunc(d); })

        paths.enter()
            .append("path")
            .classed("thread-speed", true)
            .attr("d", function(d) { return lineFunc(d); })
            .attr("fill", "none");


        paths.exit().remove();

        var timeAxis = d3.svg.axis().scale(timeScale).orient("bottom")
          .tickFormat(function(d) { return unit.millisecond(d); }) ;

        svg.selectAll(".x-axis").call(timeAxis);

        var speedAxis = d3.svg.axis().scale(speedScale).orient("left")
            .tickFormat(function(d) { return serie.unit(d); })
        svg.selectAll(".left-axis").call(speedAxis); 
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }

    return chart;
};
