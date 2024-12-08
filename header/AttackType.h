#pragma once

#include <iostream>
#include <sstream>
enum class AttackType {
    Ranged,
    Melee
};

//leave them outside
std::ostream& operator<<(std::ostream& out, const AttackType& type);
std::istream& operator>>(std::istream& in, AttackType& type);
