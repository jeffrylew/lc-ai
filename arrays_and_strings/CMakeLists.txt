set (
    cpp_files
    "3sum"
    "3sum_closest"
    "compare_version_numbers"
    "container_with_most_water"
    "first_unique_character_in_a_string"
    "group_anagrams"
    "implement_strstr"
    "integer_to_english_words"
    "integer_to_roman"
    "longest_substring_without_repeating_characters"
    "minimum_window_substring"
    "missing_number"
    "product_of_array_except_self"
    "roman_to_integer"
    "rotate_image"
    "string_to_integer_atoi"
    "two_sum"
)

foreach (cpp_file in ITEMS ${cpp_files})
    add_executable (${cpp_file}_test ${cpp_file}.cpp)

    target_link_libraries (${cpp_file}_test PRIVATE Catch2::Catch2WithMain)

    catch_discover_tests (${cpp_file}_test)
endforeach ()
