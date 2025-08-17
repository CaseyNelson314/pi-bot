#include <pigpio.h>
#include <cassert>
#include "gpio.hpp"

gpio_enabler::gpio_enabler() noexcept
{
}

gpio_enabler::~gpio_enabler()
{
}

void gpio_enabler::enable()
{
    assert(not(gpioInitialise() < 0));
}

void gpio_enabler::disable()
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

pin_pwm::~pin_pwm()    
{
    gpioSetMode(pin, PI_INPUT);  // 入力モードに戻す これをしないとHIGHが出力され続けた
}

void pin_pwm::begin()
{
    gpioSetPWMfrequency(pin, 100'000);
}

void pin_pwm::write(uint8_t angle)
{
    gpioPWM(pin, angle);
}
