#include <catch2/catch_test_macros.hpp>

#include <queue>
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

static bool canFinishDS1(int                                  numCourses,
                         const std::vector<std::vector<int>>& prerequisites)
{
    //! @details https://leetcode.com/problems/course-schedule/editorial/
    //!
    //!          Time complexity O(M + N) where M = prerequisites.size() and
    //!          N = number of courses. Initializing prereq_and_courses takes
    //!          O(M) to go through all edges. Initializing course_indegrees
    //!          also takes O(M). Each queue operation takes O(1) and a single
    //!          course/node will be pushed once, leading to O(N) operations for
    //!          N courses/nodes. We iterate over the neighbors of each course
    //!          /node that is popped out of the queue iterating over all the
    //!          edges once. Since there are a total of M edges, it would take
    //!          O(M) to iterate over the edges.
    //!          Space complexity O(M + N). course_indegrees and
    //!          prereq_and_courses take O(M) space. course_queue can have no
    //!          more than N elements in the worst-case scenario.

    //! Map of <course, number of prereqs/edges entering course>
    std::unordered_map<int, int> course_indegrees;

    //! Map of <prerequisite, courses that have this prereq>
    //! Vector contains all courses with an incoming edge from prerequisite
    std::unordered_map<int, std::vector<int>> prereq_and_courses;

    for (const auto& course_and_prereq : prerequisites)
    {
        const int course {course_and_prereq[0]};
        const int prereq {course_and_prereq[1]};

        prereq_and_courses[prereq].push_back(course);
        ++course_indegrees[course];
    }

    //! Queue for BFS moving from leaf courses/nodes to parent courses/nodes
    std::queue<int> course_queue;

    //! Push all courses with indegree zero into the queue
    for (int course = 0; course < numCourses; ++course)
    {
        if (course_indegrees.contains(course))
        {
            continue;
        }

        course_queue.push(course);
    }

    //! Count number of visited/taken courses
    int taken_courses {};

    while (!course_queue.empty())
    {
        const int course {course_queue.front()};
        course_queue.pop();
        ++taken_courses;

        if (!prereq_and_courses.contains(course))
        {
            continue;
        }

        //! neighbor_course has an incoming edge from course
        for (const auto& neighbor_course : prereq_and_courses[course])
        {
            //! Delete the edge "course -> neighbor_course"
            --course_indegrees[neighbor_course];

            if (course_indegrees[neighbor_course] == 0)
            {
                //! neighbor_course behaves as a leaf course/node
                course_queue.push(neighbor_course);
            }
        }
    }

    //! If number of courses taken/visited is less than total number of courses
    //! then return false as there must be a cycle.
    return taken_courses == numCourses;
}

static bool canFinishDS2(int                                  numCourses,
                         const std::vector<std::vector<int>>& prerequisites)
{
    //! @details https://leetcode.com/problems/course-schedule/editorial
    //!
    //!          Time complexity O(V + E) where V = numCourses and E is the size
    //!          of prerequisites. Initializing the prereq_and_courses adjacency
    //!          list takes O(E) to iterate through all edges. Initializing the
    //!          indegrees vector takes O(V). Each queue operation takes O(1)
    //!          and each course is pushed once when its indegrees is zero,
    //!          resulting in O(V) operations for V courses. We iterate over the
    //!          dependent courses of each prerequisite course that is popped in
    //!          O(E) since there are E edges total.
    //!          Space complexity O(V + E). The prereq_and_courses adjacency
    //!          list takes O(E) space and the indegrees vector takes O(V).
    //!          The queue can store no more than V courses in the worst case so
    //!          it would use O(V).

    //! Indegrees for each course
    std::vector<int> indegrees(numCourses);

    //! prereq_and_courses[i] contains all courses that have i as a prerequisite
    //! Adjacency list: All courses with an incoming edge from prerequisite i
    std::vector<std::vector<int>> prereq_and_courses(numCourses);

    for (const auto& course_and_prereq : prerequisites)
    {
        const int course {course_and_prereq[0]};
        const int prereq {course_and_prereq[1]};

        prereq_and_courses[prereq].push_back(course);
        ++indegrees[course];
    }

    //! Queue for BFS moving from leaf courses/nodes to parent courses/nodes
    //! A leaf course/node has indegree zero/no prerequisites
    std::queue<int> course_queue;

    //! Add all courses with indegree zero (no prerequisites) to course_queue
    for (int course = 0; course < numCourses; ++course)
    {
        if (indegrees[course] == 0)
        {
            course_queue.push(course);
        }
    }

    //! Count number of courses visited/taken
    int courses_taken {};

    while (!course_queue.empty())
    {
        const int prereq {course_queue.front()};
        course_queue.pop();
        ++courses_taken;

        for (const int dependent_course : prereq_and_courses[prereq])
        {
            //! Delete the edge from "prereq -> dependent_course"
            --indegrees[dependent_course];

            if (indegrees[dependent_course] == 0)
            {
                course_queue.push(dependent_course);
            }
        }
    }

    return courses_taken == numCourses;
}

static bool canFinishDS3(int                                  numCourses,
                         const std::vector<std::vector<int>>& prerequisites)
{
    //! @details https://leetcode.com/problems/course-schedule/editorial

    std::vector<std::vector<int>> adj(numCourses);

    for (const auto& prereq : prerequisites)
    {
        adj[prereq[1]].push_back(prereq[0]);
    }

    std::vector<bool> taken_courses(numCourses);
    std::vector<bool> in_stack(numCourses);

    std::function<bool(int)> dfs = [&](int course) {
        //! If the course is already in the stack then we have a cycle
        if (in_stack[course])
        {
            return true;
        }

        if (taken_courses[course])
        {
            return false;
        }

        //! @todo
    };

    for (int course = 0; course < numCourses; ++course)
    {
        if (dfs(course))
        {
            return false;
        }
    }

    return true;
}

TEST_CASE("Example 1", "[canFinish]")
{
    constexpr int numCourses {2};

    const std::vector<std::vector<int>> prerequisites {{1, 0}};

    // REQUIRE(canFinishFA(numCourses, prerequisites));
    REQUIRE(canFinishDS1(numCourses, prerequisites));
    REQUIRE(canFinishDS2(numCourses, prerequisites));
    REQUIRE(canFinishDS3(numCourses, prerequisites));
}

TEST_CASE("Example 2", "[canFinish]")
{
    constexpr int numCourses {2};

    const std::vector<std::vector<int>> prerequisites {{1, 0}, {0, 1}};

    // REQUIRE(!canFinishFA(numCourses, prerequisites));
    REQUIRE(!canFinishDS1(numCourses, prerequisites));
    REQUIRE(!canFinishDS2(numCourses, prerequisites));
    REQUIRE(!canFinishDS3(numCourses, prerequisites));
}
