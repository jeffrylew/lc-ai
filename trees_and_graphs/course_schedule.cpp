#include <catch2/catch_test_macros.hpp>

#include <unordered_map>
#include <unordered_set>
#include <vector>

static bool canFinishFA(int                                  numCourses,
                        const std::vector<std::vector<int>>& prerequisites)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/2983/

    bool can_finish {true};

    //! Map of <course, vector of prerequisites for course>
    std::unordered_map<int, std::vector<int>> course_prereqs;

    for (const auto& course_and_prereq : prerequisites)
    {
        const int course {course_and_prereq[0]};
        const int prereq {course_and_prereq[1]};

        course_prereqs[course].push_back(prereq);
    }

    std::unordered_set<int> prereqs_taken;

    for (const auto& [course, prereq_vec] : course_prereqs)
    {
        //! If detect a cycle then can_finish = false
    }

    return can_finish;
}

TEST_CASE("Example 1", "[canFinish]")
{
    constexpr int numCourses {2};

    const std::vector<std::vector<int>> prerequisites {{1, 0}};

    // REQUIRE(canFinishFA(numCourses, prerequisites));
}

TEST_CASE("Example 2", "[canFinish]")
{
    constexpr int numCourses {2};

    const std::vector<std::vector<int>> prerequisites {{1, 0}, {0, 1}};

    // REQUIRE(!canFinishFA(numCourses, prerequisites));
}
