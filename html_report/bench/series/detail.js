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
        "name": "Successes",
        "unit": unit.none,
        "lines": makeLineFunction("successes")
    },
    {
        "name": "Failures",
        "unit": unit.none,
        "lines": makeLineFunction("failures")
    },
    {
        "name": "Virtual memory usage", 
        "unit": unit.byte,
        "lines": makeLineFunction("vm_used")
    },
    {
        "name": "Physical memory usage", 
        "unit": unit.byte,
        "lines": makeLineFunction("physmem_used")
    },
    {
        "name": "Evictions",
        "unit": unit.none,
        "lines": makeLineFunction("evictions")
    },
    {
        "name": "Persisted size",
        "unit": unit.byte,
        "lines": makeLineFunction("persisted_size")
    },
    {
        "name": "Persisted count",
        "unit": unit.none,
        "lines": makeLineFunction("persisted_count")
    },
    {
        "name": "Resident size",
        "unit": unit.byte,
        "lines": makeLineFunction("resident_size")
    },
    {
        "name": "Resident count",
        "unit": unit.none,
        "lines": makeLineFunction("resident_count")
    },
    {
        "name": "SNMP: Physical memory",
        "unit": unit.byte,
        "lines": makeLineFunction("snmp.physical_memory")
    },
    {
        "name": "SNMP: Fixed disks",
        "unit": unit.byte,
        "lines": makeLineFunction("snmp.fixed_disks")
    } ,
    {
        "name": "SNMP: Swap space",
        "unit": unit.byte,
        "lines": makeLineFunction("snmp.swap_space")
    }    
];
