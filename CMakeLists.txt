cmake_minimum_required(VERSION 3.22)
project(executable)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Unit testing
###############################################################################
enable_testing()
include(CTest)

add_executable(core_deque_test_exe
    src/doctest_main.cpp
    src/core/deque.test.cpp
)

target_include_directories(core_deque_test_exe PRIVATE external)

target_link_libraries(core_deque_test_exe PRIVATE -fsanitize=address,undefined,leak)

add_test(core_deque_test core_deque_test_exe)

add_custom_target(run_deque_test ALL
    COMMAND ctest --output-on-failure
    DEPENDS core_deque_test_exe)
###############################################################################

add_executable(${PROJECT_NAME}
    src/main.cpp
)

