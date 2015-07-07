#include "test_pool.hpp"

#include <iostream>

int main(int argc, const char* argv[]) 
{
    qdb::benchmark::tests::test_pool tests;

    std::cout << "Available tests:" << std::endl;
    for(const qdb::benchmark::framework::test& test : tests)
    {
        std::cout << " - " << test.id() << ":" << std::endl;
        std::cout << "   " << test.description() << std::endl;
    }
}