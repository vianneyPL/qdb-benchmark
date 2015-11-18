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
                    var value = d3.max(tests, function(d) {
                        return key in d.scalars ? d.scalars[key].value : NaN;
                    });
                    var text = isNaN(value) ? "N/A" : bench.units[tests[0].scalars[key].unit](value);
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
