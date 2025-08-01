#pragma once

#include <cmath>
#include "range.hpp"

class servo
{
    int pin;
    float angle_limit_rad;
    range<int> pulse_range;

public:
    servo(int pin,
          float angle_limit_rad = M_PI,
          range<int>&& pulse_range_us = { 500, 2500 });

    void move(float angle_rad);
};
