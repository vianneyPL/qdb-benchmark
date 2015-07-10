#include <bench/app/program.hpp>

#include <iostream>

int main(int argc, const char* argv[]) 
{
    qdb::bench::app::program program;

    try
    {
        program.run(argc, argv);
        return EXIT_SUCCESS;
    }
    catch (std::exception &e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}