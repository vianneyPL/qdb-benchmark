if (!bench.chart) bench.chart = {}

bench.chart.overview = function() {
    var data;
    var dispatch = d3.dispatch("checked");

    function chart(container) {
        var scalars = {};

        data.forEach(function(tests) {
            tests.forEach(function(test) {
                for (var key in test.scalars) {
                    scalars[key] = test.scalars[key].name;
                }
            });
        });

        var table = container.append("table");

        var head = table.append("thead").append("tr");
        head.append("th")
            .append("input")
            .attr("type", "checkbox")
            .attr("checked", true)
            .on("change", function() {
                var tbody = table.select("tbody");
                var chks = tbody.selectAll("[type=checkbox]");
                var checked = this.checked;
                chks.property("checked", checked);
                tbody.selectAll("tr").each(function(tests) {
                    dispatch.checked(tests[0].name, checked);
                });
            });
        head.append("th").text("Test");
        d3.values(scalars).forEach(function(name) {
            head.append("th")
                .text(name);
        });

        var tbody = table.append("tbody");

        tbody.selectAll("tr")
            .data(data)
            .enter()
            .append("tr")
            .each(function(tests) {
                var row = d3.select(this);

                row.append("td")
                    .append("input")
                    .attr("type", "checkbox")
                    .attr("checked", true)
                    .on("change", function() {
                        dispatch.checked(tests[0].name, this.checked);
                    });

                row.append("td").append("label").text(tests[0].name);

                d3.keys(scalars).forEach(function(key){
                    var mathingTests = tests.filter(function(d) {
                        return key in d.scalars;
                    });
                    var value = d3.max(mathingTests, function(d) {
                        return d.scalars[key].value;
                    });
                    var text;
                    if (!isNaN(value)) {
                        var unit = mathingTests[0].scalars[key].unit;
                        text = bench.units[unit](value);
                    } else {
                        text = "N/A";
                    }
                    row.append("td").text(text);
                });
            });
    }

    chart.data = function(value) {
        data = value;
        return chart;
    }

    return d3.rebind(chart, dispatch, "on");
}
