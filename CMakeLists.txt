cmake_minimum_required(VERSION 3.22)
project(executable)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
include(CTest)

add_executable(utils_test_exe
    src/doctest_main.cpp
    src/utils.cpp
    src/utils.test.cpp
)
add_test(utils_test utils_test_exe)
target_include_directories(utils_test_exe PRIVATE external)

add_custom_command(
    TARGET utils_test_exe
    POST_BUILD
    COMMAND ctest --output-on-failure
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/utils.cpp
)

