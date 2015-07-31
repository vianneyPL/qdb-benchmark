var testSeries = [
{
    "name": "Average throughput",
    "unit": unit.byte_per_second,
    "value": function(test){
        var lastSample = test.iterations[test.iterations.length-1];
        var duration = lastSample[0];
        var iterations = d3.sum(lastSample.slice(1));
        if (duration < 1) return 0;
        return test.content_size*iterations*1000.0/duration;
    }
},
{
    "name": "Average frequency",
    "unit": unit.hertz,
    "value": function(test){
        var lastSample = test.iterations[test.iterations.length-1];
        var duration = lastSample[0];
        var iterations = d3.sum(lastSample.slice(1));
        if (duration < 1) return 0;
        return iterations*1000.0/duration;
    }
},
{
    "name": "Total iterations",
    "unit": unit.none,
    "value": function(test){
        var lastSample = test.iterations[test.iterations.length-1];
        var iterations = d3.sum(lastSample.slice(1));
        return iterations;
    }
},
{
    "name": "Test duration",
    "unit": unit.millisecond,
    "value": function(test){
        var lastSample = test.iterations[test.iterations.length-1];
        return lastSample[0];
    }
},
{
    "name": "Memory delta",
    "unit": unit.byte,
    "value": function(test){
        var before = d3.sum(test.node_memory[0].slice(1));
        var after = d3.sum(test.node_memory[test.node_memory.length-1].slice(1));
        return after - before;
    }
},
{
    "name": "Persisted size",
    "unit": unit.byte,
    "value": function(test){
        var before = d3.sum(test.persisted_size[0].slice(1));
        var after = d3.sum(test.persisted_size[test.persisted_size.length-1].slice(1));
        return after - before;
    }
},
{
    "name": "Resident size",
    "unit": unit.byte,
    "value": function(test){
        var before = d3.sum(test.resident_size[0].slice(1));
        var after = d3.sum(test.resident_size[test.resident_size.length-1].slice(1));
        return after - before;
    }
}];