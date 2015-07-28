if (!d3.chart) d3.chart = {};

d3.chart.threadSpeedChart = function() {

    var width = 600;
    var height = 600;
    var leftPadding = 80; 
    var rightPadding = 80; 
    var padding = 30; 
    var data;
    var svg;

    function speedText(x)
    {
        if (x < 1000) return x.toFixed(1) + "Hz";
        x /= 1000;
        if (x < 100) return x.toFixed(1) + "kHz";
        x /= 1000;
        if (x < 100) return x.toFixed(1) + "MHz";
        x /= 1000;
        if (x < 100) return x.toFixed(1) + "GHz";
    }

    function throughputText(x)
    {
        if (x < 1024) return x.toFixed(1) + "B/s";
        x /= 1024;
        if (x < 100) return x.toFixed(1) + "kB/s";
        x /= 1024;
        if (x < 100) return x.toFixed(1) + "MB/s";
        x /= 1024;
        if (x < 100) return x.toFixed(1) + "GB/s";
    }

    function chart(container) {

        svg = container.append("svg")
            .classed("thread-chart", true)
            .attr({
                width: width,
                height: height
            });

        svg.append("g").classed("graph", true).attr("transform", "translate("+leftPadding+")");
        svg.append("g").classed("axis", true).classed("x-axis", true).attr("transform", "translate("+leftPadding+","+(height-padding)+")");
        svg.append("g").classed("axis", true).classed("left-axis", true).attr("transform", "translate("+leftPadding+")");
        svg.append("g").classed("axis", true).classed("right-axis", true).attr("transform", "translate("+(width-rightPadding)+")");

        update();
    }

    chart.update = update;
    function update() {      

        var threads = [];
        var timeMax = data.threads[data.threads.length-1][0];

        for (var i=1; i<data.threads.length; i++)
        {
            var currentSample = data.threads[i];
            var previousSample = data.threads[i-1];

            var elapsed = currentSample[0] - previousSample[0];
            if (elapsed<1) continue;

            for (var j=0;j<currentSample.length-1;j++)
            {
                if (threads[j] == undefined) threads[j] = [];

                var iterations = currentSample[j+1] - previousSample[j+1];

                threads[j].push({
                    time: currentSample[0],
                    speed: iterations*1000.0/elapsed
                });
            }
        }

        console.log("threads.lenth", threads.length);

        var timeScale = d3.scale.linear()
            .domain([0, timeMax])
            .range([0, width-leftPadding-rightPadding]);

        var speedMax = d3.max(threads, function(points) {
            return d3.max(points, function(d) {
                return d.speed;
            });
        });
        var speedMin = d3.min(threads, function(points) {
            return d3.min(points, function(d) {
                return d.speed;
            });
        });
        var speedScale = d3.scale.linear()
            .domain([speedMin, speedMax])
            .range([height-padding, 0]);
        var throughputScale = d3.scale.linear()
            .domain([speedMin*data.content_size, speedMax*data.content_size])
            .range([height-padding, 0]);


        var lineFunc = d3.svg.line()
            .x(function(d) { return timeScale(d.time); })
            .y(function(d) { return speedScale(d.speed); })
            .interpolate("linear");

        var paths = svg.select(".graph")
            .selectAll("path")
            .classed("thread-speed", true)
            .data(threads)
            .attr("d", function(d) { return lineFunc(d); })

        paths.enter()
            .append("path")
            .classed("thread-speed", true)
            .attr("d", function(d) { return lineFunc(d); })
            .attr("fill", "none");


        paths.exit().remove();

        var timeAxis = d3.svg.axis().scale(timeScale).orient("bottom")
          .tickFormat(function(d) { return (d / 1000.0).toFixed(1) + "s"; }) ;

        svg.selectAll(".x-axis").call(timeAxis);

        var speedAxis = d3.svg.axis().scale(speedScale).orient("left")
            .tickFormat(function(d) { return speedText(d); })
        svg.selectAll(".left-axis").call(speedAxis); 

        var throughputAxis = d3.svg.axis().scale(throughputScale).orient("right")
            .tickFormat(function(d) { return throughputText(d); })
        svg.selectAll(".right-axis").call(throughputAxis); 
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }

    return chart;
};
