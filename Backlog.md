Benchmark tools - Backlog
=========================

# Features

- [X] Support all cluster configuration: localhost, remote node and multiple nodes
- [X] Support all persistence modes: transient or not
- [X] Can run on a production cluster
- [X] Leave the database in a clean state 
- [X] Allow to select the tests from the command line
- [X] Allow to choose the number of threads for each tests from the command line
- [X] Allow to choose the size of the entry from the command line
- [X] Allow to choose the duration of each test (it's simpler than the number of iteration)
- [X] Save time series of each threads
- [X] Generate detailed HTML report of each test
- [X] Generate index HTML with link to each test
- [X] Generate summary report for TeamCity
- [X] Generate plots for each threads
- [X] Generate summary plots
- [X] Download node infos like memory consumption
- [X] Plot memory consumption
- [X] Plot entry count
- [X] Automatically select horizontal or vertical bar chart
- [X] Automatically disable summary chart if there is only one test of that class
- [ ] Automatically selects the test with the highest value
- [X] Add summary information in the index page
- [ ] Show estimated run time at start
- [ ] Show actual run time at the end
- [ ] Report memory usage (min/max/average) to teamcity
- [ ] Report frequency to teamcity
- [ ] Limit test by number of iterations
- [ ] Allow to stack traces
- [ ] Sortable overview table
- [ ] Show persistent size starting from 0

# Implementation details

For a minimum duplication in test code, the framework must handle:

- [X] Loops
- [X] Threads
- [X] Time measurement
- [X] Saving

- [X] Differenciate test class and test instance
  A test class can be instanciated several times, into several instances
- [X] Test instances contains the test configuration: threads, bytes...
- [X] Test instances contains the result of each thread
- [X] Test class contains the description of the test
- [X] Some test are not size-dependent, like "int add"
- [X] Extract a generic time series class
- [X] Get rid of the overloaded term "test_runner"
- [X] Have a single time reference for the whole app (common between all tests and probes)
- [X] A single probe can generate multiple series
- [X] Do not create a thread for probes
- [X] Add thread count in the JSON
- [X] Attach dedicated probes to test classes
- [X] Remove probe class

# Tests

- [X] qdb_blob_get_noalloc
- [X] Repeated blob get
- [X] Repeated int add
- [X] Repeated deque push
- [X] Repeated blob put
- [ ] Repeated deque push pop
- [ ] Repeated set insert
