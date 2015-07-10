#include <bench/app/program.hpp>

#include <iostream>

int main(int argc, const char* argv[]) 
{
    bench::app::program program(argc, argv);

    try
    {
        program.run();
        return EXIT_SUCCESS;
    }
    catch (std::exception &e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}