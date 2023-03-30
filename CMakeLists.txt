cmake_minimum_required(VERSION 3.22)
project(visualgo_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Dependencies
###############################################################################

## raylib
set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

###############################################################################

# Unit testing
###############################################################################
enable_testing()
include(CTest)

add_executable(core_deque_test_exe
    src/doctest_main.cpp
    src/core/deque.test.cpp
)

add_executable(core_doubly_linked_list_test_exe
    src/doctest_main.cpp
    src/core/doubly_linked_list.test.cpp
)

target_include_directories(core_deque_test_exe PRIVATE external)
target_include_directories(core_doubly_linked_list_test_exe PRIVATE external)

if(NOT MSVC)
    target_link_libraries(core_deque_test_exe PRIVATE
        -fsanitize=address,undefined,leak -g
    )
    target_link_libraries(core_doubly_linked_list_test_exe PRIVATE
        -fsanitize=address,undefined,leak -g
    )
endif()

add_test(core_deque_test core_deque_test_exe)
add_test(core_doubly_linked_list_test core_doubly_linked_list_test_exe)

add_custom_target(run_deque_test ALL
    COMMAND ctest --output-on-failure
    DEPENDS core_deque_test_exe)

add_custom_target(run_doubly_linked_list_test ALL
    COMMAND ctest --output-on-failure
    DEPENDS core_doubly_linked_list_test_exe)
###############################################################################

include_directories(src)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/utils.cpp
    src/raygui_impl.cpp

    src/scene/base_scene.cpp
    src/scene/menu_scene.cpp
    src/scene/array_scene.cpp
    src/scene/dynamic_array_scene.cpp
    src/scene/linked_list_scene.cpp
    src/scene/doubly_linked_list_scene.cpp
    src/scene/circular_linked_list_scene.cpp
    src/scene/stack_scene.cpp
    src/scene/queue_scene.cpp

    src/scene/scene_registry.cpp
    src/scene/scene_options.cpp

    src/component/sidebar.cpp
    src/component/text_input.cpp
    src/component/file_dialog.cpp
    src/component/sequence_controller.cpp
)

target_link_libraries(${PROJECT_NAME} raylib)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC external)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_CURRENT_SOURCE_DIR})
