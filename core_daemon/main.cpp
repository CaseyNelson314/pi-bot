// cmake -S . -B build && cmake --build build && sudo ./build/pibot

#include <unistd.h>
#include <iostream>

#include "gpio.hpp"
#include "servo.hpp"
#include "unit.hpp"
#include "mecanum_wheel.hpp"
#include "websocket.hpp"
#include "json_parser.hpp"

static gpio_enabler enabler;

static mecanum_wheel mecanum {{
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
	motor{ pin_output{ 1 }, pin_output{ 2 }, pin_pwm{ 3 } },
}};

static servo axis1{ 17, deg_to_rad(270), { 500, 2500 } };
static servo axis2{ 18, deg_to_rad(270), { 500, 2500 } };
static servo axis3{ 19, deg_to_rad(270), { 500, 2500 } };
static servo axis4{ 20, deg_to_rad(270), { 500, 2500 } };


int main(int argc, char** argv)
{
    if (argc != 2)
        return 1;

    const int websocket_server_port = std::atoi(argv[1]);

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
                auto mecanum_power = receive_data->wheel;
                mecanum.move(mecanum_power.x, mecanum_power.y, mecanum_power.turn);

                auto arm_power = receive_data->arm;
                axis1.move(arm_power.axis1);
                axis2.move(arm_power.axis2);
                axis3.move(arm_power.axis3);
                axis4.move(arm_power.axis4);
                // std::cout
                //     << mecanum_power.x << " "
                //     << mecanum_power.y << " "
                //     << mecanum_power.turn << "\n";
                
                // std::cout
                //     << receive_data->arm.axis1 << " "
                //     << receive_data->arm.axis2 << " "
                //     << receive_data->arm.axis3 << " "
                //     << receive_data->arm.axis4 << "\n";
                return "[ OK ]";
            }
            else
            {
                return "[ NG ] Invalid json";
            }
        }
    });
}
