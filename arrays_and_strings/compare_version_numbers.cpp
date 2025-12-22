#include <catch2/catch_test_macros.hpp>

#include <string>

static int compareVersionFA(std::string version1, std::string version2)
{
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

        if (version2[v2_idx] == '.')
        {
            ++v2_dot_count;
        }

        sub_v1_val = 10 * sub_v1_val + static_cast<int>(version1[v1_idx] - '0');
        sub_v2_val = 10 * sub_v2_val + static_cast<int>(version2[v2_idx] - '0');

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

        ++v1_idx;
        ++v2_idx;
    }

    sub_v1_val = 0;
    sub_v2_val = 0;

    while (v1_idx < v1_size)
    {
        if (version1[v1_idx] == '.')
        {
            sub_v1_val = 0;
            ++v1_idx;
        }

        sub_v1_val = 10 * sub_v1_val + static_cast<int>(version1[v1_idx] - '0');
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
            ++v2_idx;
        }

        sub_v2_val = 10 * sub_v2_val + static_cast<int>(version2[v2_idx] - '0');
        if (sub_v2_val > 0)
        {
            return -1;
        }

        ++v2_idx;
    }

    return 0;
}

TEST_CASE("Example 1", "[compareVersion]")
{
    REQUIRE(-1 == compareVersionFA("1.2", "1.10"));
}

TEST_CASE("Example 2", "[compareVersion]")
{
    REQUIRE(0 == compareVersionFA("1.01", "1.001"));
}

TEST_CASE("Example 3", "[compareVersion]")
{
    REQUIRE(0 == compareVersionFA("1.0", "1.0.0.0"));
}
