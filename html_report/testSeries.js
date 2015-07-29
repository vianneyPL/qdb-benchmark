var testSeries = [
{
    "name": "Average throughput",
    "unit": unit.byte_per_second,
    "value": function(test){
        var lastSample = test.threads[test.threads.length-1];
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
        var lastSample = test.threads[test.threads.length-1];
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
        var lastSample = test.threads[test.threads.length-1];
        var iterations = d3.sum(lastSample.slice(1));
        return iterations;
    }
},
{
    "name": "Test duration",
    "unit": unit.millisecond,
    "value": function(test){
        var lastSample = test.threads[test.threads.length-1];
        return lastSample[0];
    }
},
{
    "name": "Memory delta",
    "unit": unit.byte,
    "value": function(test){
        var startMemory = d3.sum(test.qdb_node_memory[0].slice(1));
        var stopMemory = d3.sum(test.qdb_node_memory[test.qdb_node_memory.length-1].slice(1));
        return stopMemory - startMemory;
    }
}];