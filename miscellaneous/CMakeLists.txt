set (
    cpp_files
    "count_substrings_with_k-frequency_characters_i"
    "form_largest_integer_with_digits_that_add_up_to_target"
    "minimum_amount_of_damage_dealt_to_bob"
    "put_marbles_in_bags"
)

foreach (cpp_file in ITEMS ${cpp_files})
    add_executable (${cpp_file}_test ${cpp_file}.cpp)

    target_link_libraries (${cpp_file}_test PRIVATE Catch2::Catch2WithMain)

    catch_discover_tests (${cpp_file}_test)
endforeach ()
