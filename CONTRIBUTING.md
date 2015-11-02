Contributing to qdb-benchmark
=============================

# Conding convention

Please follow current naming convention.
There is a `.clang-format` at the root, so you can use clang-format.

# How to add a test?

Tests are located in `bench/tests`.

To create a new test, derive a class from `bench::tests::test_template` (it's a CTRP).
This `test_template` already implements `bench::test_class` so you don't have to worry about that.

```c++
class mytest : public test_template<mytest>
{
public:
    mytest(bench::test_config config) : qdb_test_template(config)
    {
    	// only perform instantaneous operations because it's executed on the 
        // main thread during the "schedule" phase

    	// do not throw, because it would stop the program        

        // it's NOT the right place to connect to the database, for instance 
    }

    void setup() override
    {
        // in this function you can prepare your test
        // it's the right place to connect to the data base, for instance
        // you can throw, but it will set the test as "failed"

        // if you need a long running setup, you must setup_each():
		setup_each([=](unsigned long iteration)
        	{
        		// and prepare each iteration here
        	});        
    }

    void run_iteration(unsigned long iteration)
    {
        // this is where the code under test goes
        // you can throw, it will set the test as "failed"
    }

    void cleanup() override
    {
        // in this function you restore the original state
        // it's the right place to delete entries from the data base, for instance
        // you can throw, but it will set the test as "failed"

        // if you need a long running cleanup, you must use cleanup_each():
        cleanup_each([=](unsigned long iteration)
         	{
            	// and clean each iteration here
         	});  
    }

    static ::std::string name()
    {
        return "mytest";
    }

    static ::std::string description()
    {
        return "This is the description of my test";
    }

    static bool size_dependent()
    {
    	// return true if it make sense to invoke this test with different content size
        return true;
    }
};
```

You don't need to worry about concurrency in this class.
Each thread will have its own instance of `mytest`.

However, you may want to use difference database keys to avoid conflicts.
You can use `utils::unique_alias` to help you.
