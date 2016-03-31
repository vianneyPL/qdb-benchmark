var renderTimeout;

var content = d3.select("#content");

function add_charts_for_test_class(test_name) {

    var div = d3.select(this);
    var test = tests_by_class[test_name];

    div.attr("id", test_name);
    div.append("h2").text(test_name);
    div.append("p").text(test[0].description);

    var columnCount = bench.computations.getContentSizes(test).length;
    var rowCount = bench.computations.getThreadCounts(test).length;

    if (columnCount > 1 || rowCount > 1) {
        var multiTestChart;

        if (columnCount == 1) {
            multiTestChart = bench.chart.horizontalBarChart();
        } else if (rowCount == 1) {
            multiTestChart = bench.chart.verticalBarChart();
        } else {
            multiTestChart = bench.chart.bubbleChart();
        }

        multiTestChart.data(test);
        multiTestChart(div.append("div").classed("summary", true));
        multiTestChart.on("select", function(id){
            console.log("test "+id);
            singleTestChart.data(test_by_id[id]);
            singleTestChart.update();
        });
    }

    var singleTestChart = bench.chart.lineChart();
    singleTestChart.data(test[0]);
    singleTestChart(div.append("div").classed("detail", true));
}

function render()
{
    var class_names = Object.keys(tests_by_class);

    content
        .append("h1")
            .attr("id", "overview")
            .text("Benchmark Results");

    var overview = bench.chart.overview();
    overview.data(d3.values(tests_by_class));
    overview.on("checked", function(test, checked) {
        d3.select("#"+test).style("display", checked ? "block" : "none");
    });
    overview(content.append("div").classed("overview", true));

    content
        .selectAll("div.test")
        .data(class_names)
        .enter()
        .append("div").classed("test", true)
        .each(add_charts_for_test_class);
}
