#include <catch2/catch_test_macros.hpp>

#include <string>
#include <string_view>
#include <utility>

static int strStrFA(std::string haystack, std::string needle)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2968/
    //!
    //!          Time complexity O(H) where H = haystack.size()
    //!          Space complexity O(1)

    const auto haystack_size = static_cast<int>(std::ssize(haystack));
    const auto needle_size   = static_cast<int>(std::ssize(needle));

    for (int haystack_pos = 0; haystack_pos < haystack_size; ++haystack_pos)
    {
        if (haystack_size - haystack_pos < needle_size)
        {
            return -1;
        }

        if (haystack[haystack_pos] != needle.front())
        {
            continue;
        }

        int pos_offset {1};
        while (pos_offset < needle_size)
        {
            if (haystack[haystack_pos + pos_offset] != needle[pos_offset])
            {
                break;
            }

            ++pos_offset;
        }

        if (pos_offset == needle_size)
        {
            return haystack_pos;
        }
    }

    return -1;
}

static int strStrDS1(std::string haystack, std::string needle)
{
    //! @details https://leetcode.com/problems
    //!          /find-the-index-of-the-first-occurrence-in-a-string/editorial/
    //!
    //!          Time complexity O(H * N) where H = haystack.size() and
    //!          N = needle.size(). For every window_start, we may have to
    //!          iterate at most N times. There are H - N + 1 such window_starts
    //!          which gives O((H - N + 1) * N) or O(H * N).
    //!          Space complexity O(1).

    const auto haystack_size = static_cast<int>(std::ssize(haystack));
    const auto needle_size   = static_cast<int>(std::ssize(needle));

    for (int window_start = 0;
         window_start <= haystack_size - needle_size;
         ++window_start)
    {
        for (int window_idx = 0; window_idx < needle_size; ++window_idx)
        {
            if (needle[window_idx] != haystack[window_start + window_idx])
            {
                break;
            }

            if (window_idx == needle_size - 1)
            {
                return window_start;
            }
        }
    }

    return -1;
}

[[nodiscard]] constexpr int hash_value_DS2(std::string_view str_v,
                                           int              radix,
                                           int              mod,
                                           int              needle_size)
{
    int  str_v_hash {};
    long factor {1L};

    for (int idx = needle_size - 1; idx >= 0; --idx)
    {
        str_v_hash =
            (str_v_hash + static_cast<int>(str_v[idx] - 'a') * factor) % mod;
        factor = (factor * radix) % mod;
    }

    return str_v_hash;
}

static int strStrDS2(std::string haystack, std::string needle)
{
    //! @details https://leetcode.com/problems
    //!          /find-the-index-of-the-first-occurrence-in-a-string/editorial/
    //!
    //!          Time complexity O(needle_size * haystack_size). In the worst
    //!          case, needle_hash might match the hash value of all haystack
    //!          substrings so we'd have to iterate character by character in
    //!          each window. There are haystack_size - needle_size + 1 such
    //!          windows of length needle_size. In the best case, if no hash
    //!          value of the haystack substring matches with needle_hash then
    //!          we don't have to iterate character by character in each window
    //!          for O(haystack_size + needle_size). Computing the hash value of
    //!          haystack and needle takes O(needle_size). Traversing all
    //!          windows takes O(haystack_size - needle_size). During traversal,
    //!          we do constant numbers of operations in O(haystack_size -
    //!          needle_size + 2 * needle_size) = O(haystack_size + needle_size)
    //!          Space complexity O(1). There are a handful of variables like
    //!          needle_hash, haystack_hash, window_start, etc. that use
    //!          constant space.

    const auto needle_size   = static_cast<int>(std::ssize(needle));
    const auto haystack_size = static_cast<int>(std::ssize(haystack));
    if (haystack_size < needle_size)
    {
        return -1;
    }

    constexpr int number_system_base_radix {26};
    constexpr int prime_number_mod {1000000033};
    long          max_char_weight {1L};

    for (int needle_idx = 0; needle_idx < needle_size; ++needle_idx)
    {
        max_char_weight =
            (max_char_weight * number_system_base_radix) % prime_number_mod;
    }

    //! Compute hash of needle
    constexpr long needle_hash {
        hash_value_DS2(needle,
                       number_system_base_radix,
                       prime_number_mod,
                       needle_size)};

    long haystack_hash {};

    //! Check for each needle_size-substring of haystack,
    //! starting at index window_start
    for (int window_start = 0;
         window_start <= haystack_size - needle_size;
         ++window_start)
    {
        if (window_start == 0)
        {
            //! Compute hash of the first substring
            haystack_hash = hash_value_DS2(haystack,
                                           number_system_base_radix,
                                           prime_number_mod,
                                           needle_size);
        }
        else
        {
            //! Update hash using previous hash value in O(1)
            haystack_hash =
                ((haystack_hash * number_system_base_radix) % prime_number_mod
                - (static_cast<int>(haystack[window_start - 1] - 'a')
                * max_char_weight) % prime_number_mod
                + static_cast<int>(haystack[window_start + needle_size - 1]
                - 'a') + prime_number_mod) % prime_number_mod;
        }

        //! If the hash matches, check each character
        //! since spurious hits can exist due to mod
        if (needle_hash == haystack_hash)
        {
            for (int needle_idx = 0; needle_idx < needle_size; ++needle_idx)
            {
                if (needle[needle_idx] != haystack[needle_idx + window_start])
                {
                    break;
                }

                if (needle_idx == needle_size - 1)
                {
                    return window_start;
                }
            }
        }
    }

    return -1;
}

constexpr int radix1 {26};
constexpr int radix2 {27};
constexpr int modulus1 {1000000033};
constexpr int modulus2 {2147483647};

//! @brief Return pair of hash values
std::pair<long, long> hash_pair_DS3(std::string_view str, int needle_size)
{
    long hash1 {};
    long hash2 {};
    long factor1 {1};
    long factor2 {1};

    for (int needle_idx = needle_size - 1; needle_idx >= 0; --needle_idx)
    {
        hash1 += (static_cast<int>(str[needle_idx] - 'a') * factor1) % modulus1;
        factor1 = (factor1 * radix1) % modulus1;
        hash2 += (static_cast<int>(str[needle_idx] - 'a') * factor2) % modulus2;
        factor2 = (factor2 * radix2) % modulus2;
    }

    return {hash1 % modulus1, hash2 % modulus2};
}

static int strStrDS3(std::string haystack, std::string needle)
{
    //! @details https://leetcode.com/problems
    //!          /find-the-index-of-the-first-occurrence-in-a-string/editorial/

    const auto needle_size   = static_cast<int>(std::ssize(needle));
    const auto haystack_size = static_cast<int>(std::ssize(haystack));
    if (haystack_size < needle_size)
    {
        return -1;
    }

    long max_weight1 {1L};
    long max_weight2 {1L};
    for (int needle_idx = 0; needle_idx < needle_size; ++needle_idx)
    {
        max_weight1 = (max_weight1 * radix1) % modulus1;
        max_weight2 = (max_weight2 * radix2) % modulus2;
    }

    //! Compute hash pair of needle
    const auto& [needle_hash1, needle_hash2] =
        hash_pair_DS3(needle, needle_size);
    auto haystack_hash = std::make_pair<long, long>(0L, 0L);

    //! @todo
}

TEST_CASE("Example 1", "[strStr]")
{
    const std::string haystack {"sadbutsad"};
    const std::string needle {"sad"};

    REQUIRE(0 == strStrFA(haystack, needle));
    REQUIRE(0 == strStrDS1(haystack, needle));
    REQUIRE(0 == strStrDS2(haystack, needle));
    REQUIRE(0 == strStrDS3(haystack, needle));
}

TEST_CASE("Example 2", "[strStr]")
{
    const std::string haystack {"leetcode"};
    const std::string needle {"leeto"};

    REQUIRE(-1 == strStrFA(haystack, needle));
    REQUIRE(-1 == strStrDS1(haystack, needle));
    REQUIRE(-1 == strStrDS2(haystack, needle));
    REQUIRE(-1 == strStrDS3(haystack, needle));
}
