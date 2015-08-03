var test_per_class = {};
results.forEach(function(test, i) {
    test.id = i;
    if (test_per_class[test.name] != undefined)
        test_per_class[test.name].push(test);
    else 
        test_per_class[test.name] = [test];
});
var class_names = Object.keys(test_per_class);

var content = d3.select("#content");

function add_charts_for_test_class(test) {
    var div = content.append("div").classed("test", true);

    div
        .append("h2")
            .attr("id", test[0].name)
            .text(test[0].name);

    div
        .append("p")
            .text(test[0].description);

    var summaryDiv = div.append("div").classed("summary", true);
    var detailDiv = div.append("div").classed("detail", true);

    var columnCount = bench.getContentSizes(test).length;
    var rowCount = bench.getThreadCounts(test).length;

    if (columnCount > 1 || rowCount > 1) {
        var summaryChart;

        if (columnCount == 1) {
            summaryChart = bench.chart.horizontal();
        } else if (rowCount == 1) {
            summaryChart = bench.chart.vertical();
        } else {
            summaryChart = bench.chart.bubble();
        } 

        summaryChart.data(test);     
        summaryChart(summaryDiv);
        summaryChart.on("select", function(id){
            console.log("test "+id);   
            detailChart.data(results[id]);  
            detailChart.update();      
        });
    }
    
    var detailChart = bench.chart.lineChart();
    detailChart.data(test[0]);
    detailChart(detailDiv);
}

content
    .append("h1")
        .attr("id", "overview")
        .text("Benchmark Results");

var overview = bench.chart.overview();
overview.data(d3.values(test_per_class));
overview(content.append("div").classed("overview", true));

for (var key in test_per_class)
{
    setTimeout(add_charts_for_test_class, 10, test_per_class[key]);    
}
