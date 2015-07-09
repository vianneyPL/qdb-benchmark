Benchmark tools - Backlog
=========================

# Features

- [ ] Support all cluster configuration: localhost, remote node and multiple nodes
- [ ] Support all persistence modes: transient or not
- [ ] Can run on a production cluster
- [ ] Leave the database in a clean state 
- [ ] Allow to select the tests from the command line
- [ ] Allow to choose the number of threads for each tests from the command line
- [ ] Allow to choose the size of the entry from the command line
- [ ] Allow to choose the duration of each test (it's simpler than the number of iteration)
- [ ] Save time series of each threads
- [ ] Generate detailed HTML report of each test
- [ ] Generate index HTML with link to each test
- [ ] Add summary information in the index page
- [ ] Generate summary report for TeamCity
- [ ] Generate plots for each threads
- [ ] Generate summary plots

# Implementation details

For a minimum duplication in test code, the framework must handle:

- [ ] Loops
- [ ] Threads
- [ ] Time measurement
- [ ] Saving

- [X] Differenciate test class and test instance
  A test class can be instanciated several times, into several instances
- [X] Test instances contains the test configuration: threads, bytes...
- [ ] Test instances contains the result of each thread
- [X] Test class contains the description of the test
- [ ] Some test are not size-dependent, like "int add"

# Tests

- [ ] Repeated blob put
- [ ] Repeated blob get
- [ ] Repeated int add
- [ ] Repeated queue push
- [ ] Repeated queue push pop
- [ ] Repeated set insert
