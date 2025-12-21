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

    while (v1_idx < v1_size && v2_idx < v2_size)
    {
        if (version1[v1_idx] == '.')
        {
            sub_v1_val = 0;
            ++v1_idx;
        }

        if (version2[v2_idx] == '.')
        {
            sub_v2_val = 0;
            ++v2_idx;
        }

        //! @todo
    }
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
