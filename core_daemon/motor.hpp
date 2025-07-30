#pragma once

#include <cmath>
#include <cstdint>
#include "gpio.hpp"


class motor
{
    pin_output in1;
    pin_output in2;
    pin_pwm pwm;

public:
    motor(pin_output in1, pin_output in2, pin_pwm pwm)
        : in1{ in1 }
        , in2{ in2 }
        , pwm{ pwm }
    {
    }

    void begin()
    {
        in1.begin();
        in2.begin();
        pwm.begin();
    }

    void move(int duty)
    {
        int absed_duty = std::abs(duty);
        if (absed_duty > 255)
            return;

        if (duty >= 0)
            cw(absed_duty);
        else
            ccw(absed_duty);
    }

private:
    /// @brief 正転
    void cw(uint8_t duty)
    {
        in1.write(true);
        in2.write(false);
        pwm.write(duty);
    }

    /// @brief 逆転
    void ccw(uint8_t duty)
    {
        in1.write(false);
        in2.write(true);
        pwm.write(duty);
    }
};
