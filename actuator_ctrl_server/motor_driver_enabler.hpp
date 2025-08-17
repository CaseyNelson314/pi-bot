#include "gpio.hpp"

class motor_driver_enabler
{
	pin_output stby;
public:
	motor_driver_enabler(pin_output&& stdy_pin)
		: stby{ std::move(stdy_pin) }
	{
	}

	void enable()
	{
		stby.write(true);
	}

	void disable()
	{
		stby.write(false);
	}
};

