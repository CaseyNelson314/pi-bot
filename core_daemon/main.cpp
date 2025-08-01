// cmake -S . -B build && cmake --build build && sudo ./build/pibot

#include <unistd.h>
#include <iostream>

#include "gpio.hpp"
#include "servo.hpp"
#include "unit.hpp"
#include "mecanum_wheel.hpp"
#include "websocket.hpp"
#include "json_parser.hpp"

gpio_enabler enabler;

pin_output led{ 2 };

servo hand{ 17, deg_to_rad(270), { 500, 2500 } };

mecanum_wheel mecanum {{
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
}};


int main(int argc, char** argv)
{
    if (argc != 2)
        return 1;

    const int websocket_server_port = std::atoi(argv[1]);

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

    websocket_server_start(websocket_server_config{
        .server_port = websocket_server_port,
        .on_server_start = [&websocket_server_port](bool is_start_success) {
            if (is_start_success) {
                std::cout << "[ OK ] WebSocket server activation: ws://raspberrypi.local:" << websocket_server_port << '\n';
            } else {
                std::cerr << "[ NG ] Port unavailable\n";
            }
        },
        .on_open = []() {
            std::cout << "[ OK ] client connected\n";
        },
        .on_close = []() {
            mecanum.stop();
            std::cout << "[ OK ] client disconnected\n";
        },
        .on_message = [](std::string_view message) -> std::string {
            if (const auto receive_data = parse_json(message))
            {
                std::cout
                    << receive_data->wheel.x << " "
                    << receive_data->wheel.y << " "
                    << receive_data->wheel.turn << "\n";
                std::cout
                    << receive_data->arm.axis1 << " "
                    << receive_data->arm.axis2 << " "
                    << receive_data->arm.axis3 << " "
                    << receive_data->arm.axis4 << "\n";
                return "[ OK ]";
            }
            else
            {
                return "[ NG ] Invalid json";
            }
        }
    });

    // { "wheel": { "x":0, "y":1, "turn":1 }, "arm": { "axis1":0, "axis2":0, "axis3":1, "axis4":1 }  }
    // { "wheel": { "x": 0.5, "y": 0.5, "turn": 0.1 }, "arm": { "axis1": 3.14, "axis2": 3.14, "axis3": 3.14, "axis4": 3.14 } }
}
