function makeLineFunction(serie, op) {
    return function(test) 
    {
        if (op == undefined) { 
            op = function(x) { return x; }
        }

        var lines = [];
        var samples = test[serie];
        var lineCount = samples[0].length - 1;
        for (var i=0; i<samples.length; i++)
        {
            var current = samples[i];

            for (var j=0;j<lineCount;j++)
            {
                if (lines[j] == undefined) lines[j] = [];

                var x, t, x0, t0;
                x = samples[i][j+1];
                t = samples[i][0];
                if (i > 0) { 
                    x0 = samples[i-1][j+1];
                    t0 = samples[i-1][0];
                } 

                lines[j].push({
                    "time": t,
                    "value": op(x, t, x0, t0, test)
                });
            }
        }
        return lines;
    };
}

var lineSeries = [
    {
        "name": "Frequency",
        "unit": unit.kilohertz,
        "lines": makeLineFunction("iterations", function(x, t, x0, t0) {
            if (t0 == undefined) return 0;
            return (x-x0)/(t-t0);
        })
    },
    {
        "name": "Throughput",
        "unit": unit.kilobyte_per_second,
        "lines": makeLineFunction("iterations", function(x, t, x0, t0, test) {
            if (t0 == undefined) return 0;
            return (x-x0)*test.content_size/(t-t0);
        })
    },
    {
        "name": "Iterations",
        "unit": unit.none,
        "lines": makeLineFunction("iterations")
    },
    {
        "name": "Memory usage",
        "unit": unit.byte,
        "lines": makeLineFunction("node_memory")
    },
    {
        "name": "Persisted size",
        "unit": unit.byte,
        "lines": makeLineFunction("persisted_size")
    },
    {
        "name": "Resident size",
        "unit": unit.byte,
        "lines": makeLineFunction("resident_size")
    }
];
