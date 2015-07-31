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
- [ ] Add summary information in the index page
- [X] Generate summary report for TeamCity
- [X] Generate plots for each threads
- [X] Generate summary plots
- [X] Download node infos like memory consumption
- [ ] Show estimated run time at start
- [ ] Show actual run time at the end
- [ ] Plot total speed
- [X] Plot memory consumption
- [X] Plot entry count
- [ ] Report memory usage (min/max/average) to teamcity
- [ ] Report frequency to teamcity
- [ ] Limit test by number of iterations

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

# Tests

- [X] qdb_blob_get_noalloc
- [ ] Repeated blob put
- [X] Repeated blob get
- [X] Repeated int add
- [X] Repeated queue push
- [ ] Repeated queue push pop
- [ ] Repeated set insert
