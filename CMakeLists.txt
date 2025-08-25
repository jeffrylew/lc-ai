cmake_minimum_version_required (VERSION 3.31)
project (lc-ai)

set (CXX_STANDARD 23)

Include (FetchContent)
FetchContent_Declare (
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable (Catch2)

list (APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
enable_testing ()
include (Catch)

add_subdirectory (arrays_and_strings)
# add_subdirectory (linked_lists)
add_subdirectory (trees_and_graphs)
# add_subdirectory (recursion)
add_subdirectory (sorting_and_searching)
add_subdirectory (dynamic_programming)
# add_subdirectory (design)
add_subdirectory (miscellaneous)
# add_subdirectory (other)
