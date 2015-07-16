var test_per_class = {};
results.forEach(function(x, i) {
    x.id = i;
    if (test_per_class[x.name] != undefined)
        test_per_class[x.name].push(x);
    else 
        test_per_class[x.name] = [x];
});
var class_names = Object.keys(test_per_class);

var content = d3.select("#content");

for (var key in test_per_class)
{
    if (test_per_class[key][0].content_size>0)
    {
        var div = content.append("div").classed("test", true);

        div.append("h1").text(test_per_class[key][0].name);
        div.append("p").text(test_per_class[key][0].description);

        var chart = d3.chart.speedGridChart();
        chart.data(test_per_class[key]);        

        chart(div);
        chart.on("select", function(id){
            console.log("test "+id);
        })
    }
}