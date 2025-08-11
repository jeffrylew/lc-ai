#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

//! @struct Enemy
struct Enemy
{
    //! Damage per second that enemy deals
    int damage_points {};

    /*
    //! Health points that enemy has
    int health_points {};
     */

    //! Number of seconds it takes Bob to kill this enemy
    int secs_to_kill {};

    //! Damage that enemy deals divided by number of seconds it takes to kill
    double damage_rate {};
};

//! @brief First attempt to get minimum total damage dealt before enemies die
//! @param[in] power  Bob deals power points of damage every second to one enemy
//! @param[in] damage Vector of points of damage per second that an enemy deals
//! @param[in] health Vector of health points per enemy
//! @return Minimum total amount of damage points that will be dealt
static long long minDamageFA(int               power,
                             std::vector<int>& damage,
                             std::vector<int>& health)
{
    //! @details https://leetcode.com/problems
    //!          /minimum-amount-of-damage-dealt-to-bob/description/
    //!
    //!          Time complexity O(N * log N) for descending sort of enemies
    //!          where N = number of enemies.
    //!          Space complexity O(N) for enemies vector.

    std::vector<Enemy> enemies;
    enemies.reserve(damage.size());

    long long cumulative_damage_pts {};

    for (std::size_t enemy = 0; enemy < damage.size(); ++enemy)
    {
        cumulative_damage_pts += damage[enemy];

        int        secs_to_kill {health[enemy] / power};
        const bool addtl_sec_to_kill {health[enemy] % power > 0};
        if (addtl_sec_to_kill)
        {
            ++secs_to_kill;
        }

        enemies.emplace_back(damage[enemy],
                             // health[enemy],
                             secs_to_kill,
                             static_cast<double>(damage[enemy]) / secs_to_kill);
    }

    //! Descending sort based on damage_rate
    std::sort(enemies.begin(),
              enemies.end(),
              [](const Enemy& lhs, const Enemy& rhs) {
                  return lhs.damage_rate > rhs.damage_rate;
              });

    long long min_damage_points {};
    for (const auto& enemy : enemies)
    {
        min_damage_points += cumulative_damage_pts * enemy.secs_to_kill;

        cumulative_damage_pts -= enemy.damage_points;
    }

    return min_damage_points;

} // static long long minDamageFA( ...

TEST_CASE("Example 1", "[minDamage]")
{
    constexpr int          power {4};
    const std::vector<int> damage {1, 2, 3, 4};
    const std::vector<int> health {4, 5, 6, 8};

    //! secs_to_kill: [1, 2,   2, 2]
    //! damage_rate:  [1, 1, 1.5, 2]

    //! Explanation:
    //! - Attack enemy 3 in the first two seconds, after which enemy 3 will go
    //!   down, the number of damage points dealt to Bob is 10 + 10 = 20 points.
    //! - Attack enemy 2 in the next two seconds, after which enemy 2 will go
    //!   down, the number of damage points dealt to Bob is 6 + 6 = 12 points.
    //! - Attack enemy 0 in the next second, after which enemy 0 will go down,
    //!   the number of damage points dealt to Bob is 3 points.
    //! - Attack enemy 1 in theh next two seconds, after which enemy 1 will go
    //!   down, the number of damage points dealt to Bob is 2 + 2 = 4 points.
    REQUIRE(39LL == minDamageFA(power, damage, health));
}

TEST_CASE("Example 2", "[minDamage]")
{
    constexpr int          power {1};
    const std::vector<int> damage {1, 1, 1, 1};
    const std::vector<int> health {1, 2, 3, 4};

    //! secs_to_kill: [1,   2,    3,    4]
    //! damage_rate:  [1, 0.5, 0.33, 0.25]

    //! Explanation:
    //! - Attack enemy 0 in the first second, after which enemy 0 will go down,
    //!   the number of damage points dealt to Bob is 4 points.
    //! - Attack enemy 1 in the next two seconds, after which enemy 1 will go
    //!   down, the number of damage points dealt to Bob is 3 + 3 = 6 points.
    //! - Attack enemy 2 in the next three seconds, after which enemy 2 will go
    //!   down, the number of damage points dealt to Bob is 2 + 2 + 2 = 6 points
    //! - Attack enemy 3 in the next four seconds, after which enemy 3 will go
    //!   down, the number of damage points dealt to Bob is 1 + 1 + 1 + 1 = 4.
    REQUIRE(20LL == minDamageFA(power, damage, health));
}

TEST_CASE("Example 3", "[minDamage]")
{
    constexpr int          power {8};
    const std::vector<int> damage {40};
    const std::vector<int> health {59};

    //! secs_to_kill: 8
    //! damage_rate:  5

    REQUIRE(320LL == minDamageFA(power, damage, health));
}
