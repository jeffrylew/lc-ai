#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

static int compareVersionFA(std::string version1, std::string version2)
{
    //! @details First attempt solution does not pass Example 1

    const auto v1_size = static_cast<int>(std::ssize(version1));
    const auto v2_size = static_cast<int>(std::ssize(version2));

    int sub_v1_val {};
    int sub_v2_val {};

    int v1_idx {};
    int v2_idx {};

    int v1_dot_count {};
    int v2_dot_count {};

    while (v1_idx < v1_size && v2_idx < v2_size)
    {
        if (version1[v1_idx] == '.')
        {
            ++v1_dot_count;
        }
        else
        {
            sub_v1_val =
                10 * sub_v1_val + static_cast<int>(version1[v1_idx] - '0');
        }

        if (version2[v2_idx] == '.')
        {
            ++v2_dot_count;
        }
        else
        {
            sub_v2_val =
                10 * sub_v2_val + static_cast<int>(version2[v2_idx] - '0');
        }

        /*
         * This part returns 1 for Example 1 instead of -1
         *
        if (v1_dot_count > 0 && v1_dot_count == v2_dot_count)
        {
            if (sub_v1_val < sub_v2_val)
            {
                return -1;
            }
            else if (sub_v1_val > sub_v2_val)
            {
                return 1;
            }

            sub_v1_val = 0;
            sub_v2_val = 0;
        }
         */

        ++v1_idx;
        ++v2_idx;
    }

    while (v1_idx < v1_size)
    {
        if (version1[v1_idx] == '.')
        {
            sub_v1_val = 0;
        }
        else
        {
            sub_v1_val =
                10 * sub_v1_val + static_cast<int>(version1[v1_idx] - '0');
        }

        if (sub_v1_val > 0)
        {
            return 1;
        }

        ++v1_idx;
    }

    while (v2_idx < v2_size)
    {
        if (version2[v2_idx] == '.')
        {
            sub_v2_val = 0;
        }
        else
        {
            sub_v2_val =
                10 * sub_v2_val + static_cast<int>(version2[v2_idx] - '0');
        }

        if (sub_v2_val > 0)
        {
            return -1;
        }

        ++v2_idx;
    }

    return 0;
}

static int compareVersionDS1(std::string version1, std::string version2)
{
    //! @details https://leetcode.com/problems/compare-version-numbers/editorial
    //!
    //!          Time complexity O(N * M)

    std::vector<std::string> tokens1;
    std::vector<std::string> tokens2;
    std::istringstream       iss1(version1);
    std::istringstream       iss2(version2);
    std::string              token;

    while (std::getline(iss1, token, '.'))
    {
        tokens1.push_back(std::move(token));
    }

    while (std::getline(iss2, token, '.'))
    {
        tokens2.push_back(std::move(token));
    }

    int val1 {};
    int val2 {};
    for (std::size_t idx = 0;
         idx < std::max(tokens1.size(), tokens2.size());
         ++idx)
    {
        val1 = idx < tokens1.size() ? std::stoi(tokens1[idx]) : 0;
        val2 = idx < tokens2.size() ? std::stoi(tokens2[idx]) : 0;

        if (val1 != val2)
        {
            return val1 > val2 ? 1 : -1;
        }
    }

    //! The versions are equal
    return 0;
}

TEST_CASE("Example 1", "[compareVersion]")
{
    REQUIRE(-1 == compareVersionFA("1.2", "1.10"));
    REQUIRE(-1 == compareVersionDS1("1.2", "1.10"));
}

TEST_CASE("Example 2", "[compareVersion]")
{
    REQUIRE(0 == compareVersionFA("1.01", "1.001"));
    REQUIRE(0 == compareVersionDS1("1.01", "1.001"));
}

TEST_CASE("Example 3", "[compareVersion]")
{
    REQUIRE(0 == compareVersionFA("1.0", "1.0.0.0"));
    REQUIRE(0 == compareVersionDS1("1.0", "1.0.0.0"));
}
