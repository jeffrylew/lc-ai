set (
    cpp_files
    "3sum"
    "3sum_closest"
    "compare_version_numbers"
    "container_with_most_water"
    "first_unique_character_in_a_string"
    "group_anagrams"
    "implement_strstr"
    "integer_to_roman"
    "longest_substring_without_repeating_characters"
    "roman_to_integer"
    "string_to_integer_atoi"
    "two_sum"
)

foreach (cpp_file in ITEMS ${cpp_files})
    add_executable (${cpp_file}_test ${cpp_file}.cpp)

    target_link_libraries (${cpp_file}_test PRIVATE Catch2::Catch2WithMain)

    catch_discover_tests (${cpp_file}_test)
endforeach ()
