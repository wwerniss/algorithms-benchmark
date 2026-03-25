cmake_minimum_required(VERSION 3.16)
project(AlgorithmsBenchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for the different modules
add_subdirectory(core)
add_subdirectory(app)

enable_testing()
add_subdirectory(tests)
