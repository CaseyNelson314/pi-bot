#pragma once

#include <cmath>

inline float deg_to_rad(int deg)
{
    return (2 * M_PI) * deg / 360;
}

struct vec2
{
    float x, y;
};

struct xyturn
{
    vec2 xy;
    float turn;
};

enum class direction
{
    cw,
    ccw,
};

inline int direction_to_sign(direction dir)
{
    switch (dir)
    {
    case direction::cw: return 1;
    case direction::ccw: return -1;
    default: return 0;  // unreachable
    }
}
