if (!d3.chart) d3.chart = {};

d3.chart.speedGridChart = function() {

    var width = 600;
    var height = 600;
    var padding = 30; 
    var dispatch = d3.dispatch(chart, "select");
    var data;

    function chart(container) {
        var points = [];
        data.forEach(function(test){

            var iterations = d3.sum(test.threads, function(thread) {
                return thread.iterations[thread.iterations.length-1];
            });
            var time = d3.max(test.threads, function(thread) {
                return thread.times[thread.times.length-1];
            });

            points.push({
                id: test.id,
                threads: test.threads.length,
                size: test.content_size,
                speed: test.content_size*iterations/time
            });
        });

        points.sort(function(a, b){return a.speed-b.speed})

        var sizeValues = d3.set(points.map(function(d){return d.size})).values();
        var threadsValues = d3.set(points.map(function(d){return d.threads})).values();
        var speedExtent = d3.extent(points, function(d) {return d.speed});

        var d = d3.min([(width-padding*2) / sizeValues.length, (height-padding*2) / threadsValues.length]) - 2;    

        var sizeScale = d3.scale.ordinal().domain(sizeValues).rangePoints([d/2+padding,width-d/2-padding]);
        var threadsScale = d3.scale.ordinal().domain(threadsValues).rangePoints([d/2+padding,height-d/2-padding]);
        var speedScale = d3.scale.linear().domain(speedExtent).range([10,d]);

        var svg = container.append("svg");

        svg.attr({
            width: width,
            height: height
        })

        var chart = svg.append("g").classed("grid-chart", true).attr("transform", "translate("+padding+")");

        var dotType = "circle";

        chart.selectAll(dotType)
            .data(points)
            .enter()
            .append(dotType)
            .classed("point", true)
            .attr({
                cx: function(d) { return sizeScale(d.size) },
                cy: function(d) { return threadsScale(d.threads) },
                r: function(d) { return speedScale(d.speed)/2 }
            })
            .on("click", function(d) {
                chart.selectAll(dotType).classed("selected", false);
                d3.select(this).classed("selected", true);
                dispatch.select(d.id);
            });

        function speedText(x)
        {
            if (x < 1024) return x.toFixed(0) + "B/s";
            x /= 1024;
            if (x < 1024) return x.toFixed(0) + "kB/s";
            x /= 1024;
            if (x < 1024) return x.toFixed(0) + "MB/s";
            x /= 1024;
            if (x < 1024) return x.toFixed(0) + "GB/s";
        }

        chart.selectAll("text")
            .data(points.slice(points.length-1))
            .enter()
            .append("text")
            .attr({
                x: function(d) { return sizeScale(d.size) },
                y: function(d) { return threadsScale(d.threads) },
                "text-anchor": "middle",
                "dominant-baseline": "central",
                "pointer-events": "none"
            })
            .text(function(d){
                return speedText(d.speed)
            });
            

        var sizeAxis = d3.svg.axis().scale(sizeScale).orient("bottom");
        chart.append("g").classed("axis", true).attr("transform", "translate(0,"+(height-padding)+")").call(sizeAxis);

        var threadsAxis = d3.svg.axis().scale(threadsScale).orient("left");
        chart.append("g").classed("axis", true).call(threadsAxis);
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }



    return d3.rebind(chart, dispatch, "on");
};
