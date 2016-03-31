if (bench == undefined) bench = {};

bench.computations =
{
    transformSamples: function(samples, operation) {
        var lines = [];
        var lineCount = samples[0].length - 1;
        for (var i=0; i<samples.length; i++)
        {
            var t, t0;
            t = samples[i][0];
            if (i>0) t0 = samples[i-1][0];

            lines.push([t]);

            for (var j=0;j<lineCount;j++)
            {
                var x, x0;
                x = samples[i][j+1];
                if (i > 0) x0 = samples[i-1][j+1];

                lines[i].push(operation(x, t, x0, t0));
            }
        }
        return lines;
    },

    getThreadCounts: function(testCollection) {
        return d3.set(
            testCollection.map(
                function(test) {
                    return test.thread_count
                })
            ).values();
    },

    getContentSizes: function(testCollection) {
        return d3.set(
            testCollection.map(
                function(test) {
                    return test.content_size
                })
            ).values();
    },

    getContentCounts: function(testCollection) {
        return d3.set(
            testCollection.map(
                function(test) {
                    return test.content_count
                })
            ).values();
    }
}
