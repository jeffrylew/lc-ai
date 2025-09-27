set (
    cpp_files
    "prison_cells_after_n_days"
)

foreach (cpp_file in ITEMS ${cpp_files})
    add_executable (${cpp_file}_test ${cpp_file}.cpp)

    target_link_libraries (${cpp_file}_test PRIVATE Catch2::Catch2WithMain)

    catch_discover_tests (${cpp_file}_test)
endforeach ()
