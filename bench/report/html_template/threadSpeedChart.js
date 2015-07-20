if (!d3.chart) d3.chart = {};

d3.chart.threadSpeedChart = function() {

    var width = 600;
    var height = 600;
    var leftPadding = 100; 
    var padding = 30; 
    var data;


    function speedText(x)
    {
        if (x < 1024) return x.toFixed(2) + "B/s";
        x /= 1024;
        if (x < 1024) return x.toFixed(2) + "kB/s";
        x /= 1024;
        if (x < 1024) return x.toFixed(2) + "MB/s";
        x /= 1024;
        if (x < 1024) return x.toFixed(2) + "GB/s";
    }

    function chart(container) {

        var svg = container.append("svg")
            .classed("thread-chart", true)
            .attr({
                width: width,
                height: height
            })

        var threads = [];

        data.threads.forEach(function(thread){

            var points = [];

            for (var i=1; i<thread.times.length; i++)
            {
                var elapsed = thread.times[i] - thread.times[i-1];
                if (elapsed<1) continue;
                var iterations = thread.iterations[i] - thread.iterations[i-1];
                points.push({
                    time: thread.times[i],
                    speed: data.content_size*iterations/elapsed
                });
            }

            threads.push(points);
        });

        console.log(threads);

        var timeMax = d3.max(threads, function(points) {
            return points[points.length-1].time;
        });
        var timeScale = d3.scale.linear()
            .domain([0, timeMax])
            .range([0, width-leftPadding]);

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
        console.log("speedMax", speedMax);

        var lineFunc = d3.svg.line()
            .x(function(d) { return timeScale(d.time); })
            .y(function(d) { return speedScale(d.speed); })
            .interpolate("linear");

        var graph = svg.append("g").attr("transform", "translate("+leftPadding+")");

        for (var j = 0; j < threads.length; j++) {
            
            graph.append("path")
                .classed("thread-speed", true)
                .attr("d", lineFunc(threads[j]))
                .attr("fill", "none");
        }     

        var timeAxis = d3.svg.axis().scale(timeScale).orient("bottom")
          .tickFormat(function(d) { return (d / 1000.0).toFixed(1) + "s"; }) ;

        graph.append("g").classed("axis", true).attr("transform", "translate(0,"+(height-padding)+")").call(timeAxis);

        var speedAxis = d3.svg.axis().scale(speedScale).orient("left")
            .tickFormat(function(d) { return speedText(d); })
        graph.append("g").classed("axis", true).call(speedAxis); 

    }

    chart.data = function(value) {
        data = value;
        return chart;
    }

    return chart;
};
