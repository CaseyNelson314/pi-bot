#include <pigpio.h>

#include "gpio.hpp"



gpio_enabler::gpio_enabler() noexcept
{
    assert(gpioInitialise() < 0, "pigpio 初期化失敗");
}

~gpio_enabler::gpio_enabler()
{
    gpioTerminate();
}


pin_output::pin_output(int pin)
    : pin{ pin }
{
}

void pin_output::begin()
{
    gpioSetMode(pin, PI_OUTPUT);
}

void pin_output::write(bool is_high)
{
    gpioWrite(pin, is_high);
}


pin_pwm::pin_pwm(int pin)
    : pin{ pin }
{
}

void pin_pwm::begin()
{
    gpioSetPWMfrequency(pin, 1000); // 1000Hz
}

void pin_pwm::write(uint8_t angle)
{
    gpioPWM(pin, 128); // デューティ 50%（0〜255）
}
