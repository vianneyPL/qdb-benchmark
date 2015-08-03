bench.series.overview = [
{
    "name": "Frequency",
    "unit": unit.hertz,
    "value": function(tests){
        return d3.max(tests, function(test) {
            return bench.series.tests.averageFrequency.value(test);
        });
    }
},
{
    "name": "Throughput",
    "unit": unit.byte_per_second,
    "value": function(tests){
        return d3.max(tests, function(test) {
            return bench.series.tests.averageThroughput.value(test);
        });
    }
},
{
    "name": "Memory",
    "unit": unit.byte,
    "value": function(tests){
        return d3.max(tests, function(test) {
            return bench.series.tests.memoryDelta.value(test);
        });
    }
},
{
    "name": "Resident",
    "unit": unit.byte,
    "value": function(tests){
        return d3.max(tests, function(test) {
            return bench.series.tests.residentSizeDelta.value(test);
        });
    }
},
{
    "name": "Persised",
    "unit": unit.byte,
    "value": function(tests){
        return d3.max(tests, function(test) {
            return bench.series.tests.persistedSizeDelta.value(test);
        });
    }
}];
