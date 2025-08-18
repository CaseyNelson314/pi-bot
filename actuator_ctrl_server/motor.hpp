#pragma once

#include <cmath>
#include <cstdint>
#include "gpio.hpp"
#include "type.hpp"


class motor
{
    pin_output in1;
    pin_output in2;
    pin_pwm pwm;
    direction dir;

public:
    motor(pin_output in1, pin_output in2, pin_pwm pwm, direction dir)
        : in1{ in1 }
        , in2{ in2 }
        , pwm{ pwm }
        , dir{ dir }
    {
    }

    ~motor()
    {
        stop();
    }

    void begin()
    {
        in1.begin();
        in2.begin();
        pwm.begin();
        stop();
    }

    void move(int duty_ref)
    {
        const int duty = duty_ref * direction_to_sign(dir);
        if (std::abs(duty) > 255)
            return;

        if (duty == 0)
            stop();
        else if (duty > 0)
            cw(std::abs(duty));
        else
            ccw(std::abs(duty));
    }

    void stop()
    {
        in1.write(true);
        in2.write(true);
        pwm.write(0);
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
