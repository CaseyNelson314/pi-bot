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
