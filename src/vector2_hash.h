#pragma once
#include <raylib.h>
#include <functional>

struct Vector2Hash {
    std::size_t operator()(const Vector2& v) const {
        return std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1);
    }
};

struct Vector2Equal {
    bool operator()(const Vector2& lhs, const Vector2& rhs) const {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

inline bool operator==(const Vector2& lhs, const Vector2& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}