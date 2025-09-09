set (
    cpp_files
    "binary_tree_level_order_traversal"
    "binary_tree_zigzag_level_order_traversal"
    "course_schedule"
    "maximum_depth_of_binary_tree"
    "number_of_islands"
    "symmetric_tree"
    "validate_binary_search_tree"
    "word_ladder"
)

foreach (cpp_file in ITEMS ${cpp_files})
    add_executable (${cpp_file}_test ${cpp_file}.cpp)

    target_link_libraries (${cpp_file}_test PRIVATE Catch2::Catch2WithMain)

    catch_discover_tests (${cpp_file}_test)
endforeach ()
