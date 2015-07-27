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

function add_charts_for_test_class(test)
{
    var div = content.append("div").classed("test", true);

    div.append("h1").text(test[0].name);
    div.append("p").text(test[0].description);

    if (test[0].content_size > 0)
    {
        var gridChart = d3.chart.speedGridChart();
        gridChart.data(test);     
        gridChart(div);
        gridChart.on("select", function(id){
            console.log("test "+id);   
            detailChart.data(results[id]);  
            detailChart.update();      
        });
    }
    else
    {
        var barChart = d3.chart.speedBarChart();
        barChart.data(test);     
        barChart(div);
        barChart.on("select", function(id){
            console.log("test "+id);   
            detailChart.data(results[id]);  
            detailChart.update();      
        });
    }

    var detailChart = d3.chart.threadSpeedChart();
    detailChart.data(test[0]);
    detailChart(div);
}

for (var key in test_per_class)
{
    setTimeout(add_charts_for_test_class, 10, test_per_class[key]);    
}
