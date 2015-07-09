#include "test_pool.hpp"

#include <iostream>

int main(int argc, const char* argv[]) 
{
    qdb::benchmark::tests::test_pool tests;

    std::cout << "Available tests:" << std::endl;
    for(auto& test : tests)
    {
        std::cout << " - " << test.info().id << ":" << std::endl;
        std::cout << "   " << test.info().description << std::endl;
    }
}