if (!bench.chart) bench.chart = {}

bench.chart.overview = function() {
    var data

    function chart(container) {
        var table = container.append("table");

        var head = table.append("thead").append("tr");
        head.append("th").text("Test");
        bench.series.overview.forEach(function(serie) {
            head.append("th").text(serie.name);
        });

        var tbody = table.append("tbody");

        data.forEach(function(tests) {
            var row = tbody.append("tr");
            row.append("td").text(tests[0].name);

             bench.series.overview.forEach(function(serie) {
                 row.append("td").text(serie.unit(serie.value(tests)));
             });
        });
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }

    return chart;
}