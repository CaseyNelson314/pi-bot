#include <pigpio.h>
#include <unistd.h>
#include <iostream>


class pin_output
{
	int pin;

public:
	pin_output(int pin)
		: pin{ pin }
	{}

	void begin()
	{
		gpioSetMode(pin, PI_OUTPUT);
	}

	void write(bool is_high)
	{
		gpioWrite(pin, is_high);
	}
};

pin_output led{ 2 };

int main()
{
    if (gpioInitialise() < 0) return 1;

	led.begin();

	for ( ;; )
	{
		led.write(true);
		std::cout << "hi\n";
		sleep(1);

		led.write(false);
		std::cout << "lo\n";
		sleep(1);
	}

	gpioTerminate();
	return 0;
}
