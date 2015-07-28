if (!d3.chart) d3.chart = {};

d3.chart.speedBarChart = function() {

    var width = 600;
    var height = 600;
    var padding = 30; 
    var dispatch = d3.dispatch(chart, "select");
    var data;

    function chart(container) {
        var points = [];
        data.forEach(function(test){

            var time = test.threads[test.threads.length-1][0];
            var iterations = d3.sum(test.threads[test.threads.length-1].slice(1));

            points.push({
                id: test.id,
                threads: test.threads[0].length-1,
                speed: iterations*1000.0/time
            });
        });

        points.sort(function(a, b){return a.speed-b.speed})

        var threadsValues = d3.set(points.map(function(d){return d.threads})).values();
        var speedExtent = d3.extent(points, function(d) {return d.speed});

        var threadsScale = d3.scale.ordinal().domain(threadsValues).rangeBands([padding,height-padding], 0.5);
        var speedScale = d3.scale.linear().domain(speedExtent).range([padding,width-padding]);

        var svg = container.append("svg")
            .classed("grid-chart", true)
            .attr({
                width: width,
                height: height
            });

        var graph = svg.append("g").classed("graph", true).attr("transform", "translate("+padding+")");

        graph.selectAll("rect")
            .data(points)
            .enter()
            .append("rect")
            .classed("point", true)
            .attr({
                x: 0,
                y: function(d) { return threadsScale(d.threads) },
                width: function(d) { return speedScale(d.speed) },
                height: threadsScale.rangeBand()
            })
            .on("click", function(d) {
                graph.selectAll("rect").classed("selected", false);
                d3.select(this).classed("selected", true);
                dispatch.select(d.id);
            });

        function speedText(x)
        {
            if (x < 1000) return x.toFixed(0) + "Hz";
            x /= 1000;
            if (x < 1000) return x.toFixed(0) + "kHz";
            x /= 1000;
            if (x < 1000) return x.toFixed(0) + "MHz";
            x /= 1000;
            if (x < 1000) return x.toFixed(0) + "GHz";
        }

        graph.selectAll("text")
            .data(points.slice(points.length-1))
            .enter()
            .append("text")
            .attr({
                x: function(d) {return speedScale(d.speed) - 10},
                y: function(d) { return threadsScale(d.threads) +threadsScale.rangeBand() / 2  },
                "text-anchor": "end",
                "dominant-baseline": "central",
                "pointer-events": "none"
            })
            .text(function(d){
                return speedText(d.speed)
            });
            


        var threadsAxis = d3.svg.axis().scale(threadsScale).orient("left");
        svg.append("g").classed("axis", true).attr("transform", "translate("+padding+",0)").call(threadsAxis);
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }



    return d3.rebind(chart, dispatch, "on");
};
