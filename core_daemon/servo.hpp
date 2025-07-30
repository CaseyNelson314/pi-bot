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
          range<int>&& pulse_range_us = { 500, 2500 })
        : pin{ pin }
        , angle_limit_rad{ angle_limit_rad }
        , pulse_range{ std::move(pulse_range_us) }
    {
    }

    void move(float angle_rad)
    {
        const float angle_to_pulse = (angle_rad / angle_limit_rad) * pulse_range.diff() + pulse_range.min;
        gpioServo(pin, angle_rad * angle_to_pulse);
    }
};
