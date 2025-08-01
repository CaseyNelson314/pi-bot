#include <unistd.h>
#include <iostream>
#include <App.h>


#include "gpio.hpp"
#include "servo.hpp"
#include "unit.hpp"
#include "mecanum_wheel.hpp"

gpio_enabler enabler;

pin_output led{ 2 };

servo hand{ 17, deg_to_rad(270), { 500, 2500 } };

mecanum_wheel mecanum {{
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
}};


int main()
{
    //led.begin();
    //mecanum.begin();

    // for (;;)
    // {
	// hand.move(0);
	// sleep(1);
	// hand.move(deg_to_rad(270));
	// sleep(1);
    //     // led.write(true);
    //     // std::cout << "hi\n";
    //     // sleep(1);

    //     // led.write(false);
    //     // std::cout << "lo\n";
    //     // sleep(1);

	// 	// hand.move(0);
    //     // sleep(1);
	// 	// hand.move(M_PI);
    //     // sleep(1);

	// 	mecanum.move(0.5, 0.5, 0);
    // }
    struct UserData
    {};

    uWS::App().ws<UserData>("/", {
        .open = [](auto */*ws*/) {
            std::cout << "[ OK ] client connected\n";
        },
        .message = [](auto *ws, std::string_view msg, uWS::OpCode opCode) {
            try {
                std::cout << "[ OK ] " << msg << std::endl;
            } catch (...) {
                std::cerr << "[ NG ] json invalid.\n";
            }
            ws->send(msg, opCode, false);
        },
        .close = [](auto */*ws*/, int /*code*/, std::string_view /*message*/) {
            std::cout << "[ OK ] client disconnected\n";
        }
    }).listen(9001, [](auto *token) {
        if (token) {
            std::cout << "[ OK ] WebSocket server activation: ws://raspberrypi.local:9001\n";
        } else {
            std::cerr << "[ NG ] Port unavailable\n";
        }
    }).run();

    return 0;
}
