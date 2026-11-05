#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q6; see 题面.pdf.
namespace aim::q6 {
struct Target { int id; int x; int y; int hp; bool visible; };

// BEGIN IMPLEMENTATION
int select_target(const std::vector<Target>& targets, int max_range) {
    if (max_range < 0 || targets.empty()) {
        return -1;
    }

    const long long range = max_range;
    const long long rangeSquared = range * range;
    bool found = false;
    int bestId = -1;
    int bestHp = 0;
    long long bestDistanceSquared = 0;

    for (const Target& target : targets) {
        if (!target.visible || target.hp <= 0) {
            continue;
        }

        const long long dx = target.x;
        const long long dy = target.y;
        const long long distanceSquared = dx * dx + dy * dy;
        if (distanceSquared > rangeSquared) {
            continue;
        }

        if (!found || target.hp < bestHp ||
            (target.hp == bestHp &&
             (distanceSquared < bestDistanceSquared ||
              (distanceSquared == bestDistanceSquared && target.id < bestId)))) {
            found = true;
            bestId = target.id;
            bestHp = target.hp;
            bestDistanceSquared = distanceSquared;
        }
    }

    return found ? bestId : -1;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q6;
int main() {
    try {
        { CHECK(select_target({{7,3,4,20,true},{2,0,5,20,true}},5)==2); }
        { CHECK(select_target({},5)==-1); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
