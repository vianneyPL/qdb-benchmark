var tests_by_class = {};
var test_by_id = [];

function addTestResult(test) {

    test.series["test.frequency"] = {
        "name": "Test Frequency",
        "unit": "kilohertz",
        "samples": bench.computations.transformSamples(test.series["test.iterations"].samples,
            function(x, t, x0, t0) {
                if (t0 == undefined) return 0;
                if (t0 >= t) return 0;
                return (x-x0)/(t-t0);
            })};

    test.scalars = {}

    var lastSample = test.series["test.iterations"].samples[test.series["test.iterations"].samples.length-1];
    var totalTime = lastSample[0];
    var totalIterations = d3.sum(lastSample, function(x,i){return i>0?x:0;})

    test.scalars["test.iterations"] = {
        "name": "Iterations",
        "unit": "none",
        "value": totalIterations
    };

    test.scalars["test.frequency.average"] = {
        "name": "Frequency",
        "unit": "kilohertz",
        "value": totalIterations/totalTime
    };

    if (test.content_size>0)
    {
        test.series["test.throughput"] = {
            "name": "Throughput",
            "unit": "kilobytes/second",
            "samples": bench.computations.transformSamples(test.series["test.frequency"].samples,
                function(x) {
                    return x*test.content_size;
                })
            };

        test.series["test.volume"] = {
            "name": "Volume",
            "unit": "bytes",
            "samples": bench.computations.transformSamples(test.series["test.iterations"].samples,
                function(x) {
                    return x*test.content_size;
                })
            };

        test.scalars["test.throughput.average"] = {
            "name": "Throughput",
            "unit": "kilobytes/second",
            "value": totalIterations*test.content_size/totalTime
        };

        test.scalars["test.volume"] = {
            "name": "Volume",
            "unit": "bytes",
            "value": totalIterations*test.content_size
        };
    }

    test.id = test_by_id.length;
    test_by_id.push(test);

    if (tests_by_class[test.name] != undefined)
        tests_by_class[test.name].push(test);
    else 
        tests_by_class[test.name] = [test];

    clearTimeout(renderTimeout);
    renderTimeout = setTimeout(render);
}