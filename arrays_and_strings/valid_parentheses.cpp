#include <catch2/catch_test_macros.hpp>

#include <stack>
#include <string>
#include <unordered_map>

static bool isValidFA(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2972/

    const std::unordered_map<char, char> matching_brackets {
        {'(', ')'}, {'{', '}'}, {'[', ']'}};

    std::stack<char> left_brackets;
    for (const char curr_bracket : s)
    {
        if (matching_brackets.contains(curr_bracket))
        {
            left_brackets.push(curr_bracket);
            continue;
        }

        if (left_brackets.empty())
        {
            return false;
        }

        const char prev_left_bracket {left_brackets.top()};
        left_brackets.pop();

        if (matching_brackets.at(prev_left_bracket) != curr_bracket)
        {
            return false;
        }
    }

    return left_brackets.empty();
}

TEST_CASE("Example 1", "[isValid]")
{
    REQUIRE(isValidFA("()"));
}

TEST_CASE("Example 2", "[isValid]")
{
    REQUIRE(isValidFA("()[]{}"));
}

TEST_CASE("Example 3", "[isValid]")
{
    REQUIRE(!isValidFA("(]"));
}

TEST_CASE("Example 4", "[isValid]")
{
    REQUIRE(isValidFA("([])"));
}

TEST_CASE("Example 5", "[isValid]")
{
    REQUIRE(!isValidFA("([)]"));
}
