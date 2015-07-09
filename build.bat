@setlocal
@mkdir build
cd build        || @exit /b 1 
cmake ..        || @exit /b 1
cmake --build . || @exit /b 3
ctest -VV .     || @exit /b 4