if (typeof bench === 'undefined') bench = {}
if (!bench.series) bench.series = {}

bench.series.tests = {
    "averageFrequency": {
        "name": "Average frequency",
        "unit": unit.hertz,
        "value": function(test) {
            if (!test.iterations) return undefined;
            var lastSample = test.iterations[test.iterations.length-1];
            var duration = lastSample[0];
            var iterations = d3.sum(lastSample.slice(1));
            if (duration < 1) return 0;
            return iterations*1000.0/duration;
        }},
    "averageThroughput": {
        "name": "Average throughput",
        "unit": unit.byte_per_second,
        "value": function(test) {
            if (!test.iterations) return undefined;
            var lastSample = test.iterations[test.iterations.length-1];
            var duration = lastSample[0];
            var iterations = d3.sum(lastSample.slice(1));
            if (duration < 1) return 0;
            return test.content_size*iterations*1000.0/duration;
        }},
    "totalIterations": {
        "name": "Total iterations",
        "unit": unit.none,
        "value": function(test) {
            if (!test.iterations) return undefined;
            var lastSample = test.iterations[test.iterations.length-1];
            var iterations = d3.sum(lastSample.slice(1));
            return iterations;
        }},
    "testDuration": {
        "name": "Test duration",
        "unit": unit.millisecond,
        "value": function(test) {
            if (!test.iterations) return undefined;
            var lastSample = test.iterations[test.iterations.length-1];
            return lastSample[0];
        }},
    "memoryDelta": {
        "name": "Memory delta",
        "unit": unit.byte,
        "value": function(test) {
            if (!test.node_memory) return undefined;
            var before = d3.sum(test.node_memory[0].slice(1));
            var after = d3.sum(test.node_memory[test.node_memory.length-1].slice(1));
            return after - before;
        }},
    "persistedSizeDelta": {
        "name": "Persisted size delta",
        "unit": unit.byte,
        "value": function(test) {
            if (!test.persisted_size) return undefined;
            var before = d3.sum(test.persisted_size[0].slice(1));
            var after = d3.sum(test.persisted_size[test.persisted_size.length-1].slice(1));
            return after - before;
        }},
    "residentSizeDelta": {
        "name": "Resident size delta",
        "unit": unit.byte,
        "value": function(test) {
            if (!test.resident_size) return undefined;
            var before = d3.sum(test.resident_size[0].slice(1));
            var after = d3.sum(test.resident_size[test.resident_size.length-1].slice(1));
            return after - before;
        }}
    };

bench.getValueExtent = function (testCollection, serie) {
    var extent = d3.extent(testCollection, function(d) {
        return serie.value(d)
    });

    if (extent[0] != extent[1]) {
        return extent;
    } else if (extent[0] == 0) {
        return [-1, 1];
    } else {
        return [extent[0]*0.9, extent[1]*1.1];
    }
}

bench.getThreadCounts = function(testCollection) {
    return d3.set(
        testCollection.map(
            function(test) {
                return test.thread_count
            })
        ).values();
}

bench.getContentSizes = function(testCollection) {
    return d3.set(
        testCollection.map(
            function(test) {
                return test.content_size
            })
        ).values();
}
