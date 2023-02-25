cmake_minimum_required(VERSION 3.22)
project(executable)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE RELWITHDEBINFO) # improve Catch2 link time for MinGW

# Fetch Catch2
#######################################
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

#######################################

enable_testing()
include(CTest)

add_executable(utils_test_exe
    src/utils.cpp
    src/utils.test.cpp
)
target_link_libraries(utils_test_exe PRIVATE Catch2::Catch2WithMain)

add_test(utils_test utils_test_exe)

add_custom_command(
    TARGET utils_test_exe
    POST_BUILD
    COMMAND ctest --output-on-failure
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/utils.cpp
)

