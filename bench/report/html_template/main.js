var test_per_class = {};
results.forEach(function(x) {
    if (test_per_class[x.id] != undefined)
        test_per_class[x.id].push(x);
    else 
        test_per_class[x.id] = [x];
});
var class_names = Object.keys(test_per_class);

var content = d3.select("#content");

for (var key in test_per_class)
{
    if (test_per_class[key][0].content_size>0)
        add_test_class(test_per_class[key]);
}

function add_test_class(tests)
{
    var w = 500;
    var h = 500;
    var pad = 30;

    var div = content.append("div").classed("test", true);

    div.append("h1").text(tests[0].id);
    div.append("p").text(tests[0].description);

    var points = [];
    tests.forEach(function(test){

        var iterations = d3.sum(test.threads, function(thread) {
            return thread.iterations[thread.iterations.length-1];
        });
        var time = d3.max(test.threads, function(thread) {
            return thread.times[thread.times.length-1];
        });

        points.push({
            threads: test.threads.length,
            size: test.content_size,
            speed: test.content_size*iterations/time
        });
    });

    points.sort(function(a, b){return a.speed-b.speed})

    var sizeValues = d3.set(points.map(function(d){return d.size})).values();
    var threadsValues = d3.set(points.map(function(d){return d.threads})).values();
    var speedExtent = d3.extent(points, function(d) {return d.speed});

    console.log("sizeValues", sizeValues);
    console.log("threadsValues", threadsValues);
    console.log("speedExtent", speedExtent);

    var d = d3.min([(w-pad*2) / sizeValues.length, (h-pad*2) / threadsValues.length]) - 2;    

    var sizeScale = d3.scale.ordinal().domain(sizeValues).rangePoints([d/2+pad,w-d/2-pad]);
    var threadsScale = d3.scale.ordinal().domain(threadsValues).rangePoints([d/2+pad,h-d/2-pad]);
    var speedScale = d3.scale.linear().domain(speedExtent).range([5,d]);

    var svg = div.append("svg");

    svg.attr({
        width: w,
        height: h
    })

    var chart = svg.append("g").classed("chart", true).attr("transform", "translate("+pad+")");

    chart.selectAll("rect")
        .data(points)
        .enter()
        .append("rect")
        .attr({
            x: function(d) { return sizeScale(d.size)-speedScale(d.speed)/2 },
            y: function(d) { return threadsScale(d.threads)-speedScale(d.speed)/2 },
            width: function(d) { return speedScale(d.speed) },
            height: function(d) { return speedScale(d.speed) },
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
            "pointer-events": "none"
        })
        .text(function(d){
            return speedText(d.speed)
        });
        

    var sizeAxis = d3.svg.axis().scale(sizeScale).orient("bottom");
    chart.append("g").classed("axis", true).attr("transform", "translate(0,"+(h-pad)+")").call(sizeAxis);

    var threadsAxis = d3.svg.axis().scale(threadsScale).orient("left");
    chart.append("g").classed("axis", true).call(threadsAxis);

    var tooltip = chart.append("rectangle").text("coucou")

    /*for (var i=0; i<tests.length; i++)
    {

    }
    for (var i=0; i<tests[0].threads[0].times.length; i++) {
        thread0.push({
            time: tests[0].threads[0].times[i],
            iterations: tests[0].threads[0].times[i]
        });
    };

    var timeExtent = d3.extent(thread0, function(d) {
        return d.time;
    });

    var timeScale = d3.scale.linear().domain(timeExtent).range([0,100]);
    

    console.log(timeExtent);

    svg.selectAll("circle")
        .data(thread0)
        .enter()
        .append("circle")
        .attr({
            cx: function(d) {return timeScale(d.time);},
            cy: function(d) {return d.iterations},
            r: 40,
            fill: "#666666"
        });

    console.log(tests[0].id, tests);*/
}