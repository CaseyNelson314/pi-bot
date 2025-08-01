#pragma once

#include <functional>

struct websocket_server_config
{
    int server_port;
    std::function<void(bool)> on_server_start;
    std::function<void(void)> on_open;
    std::function<void(void)> on_close;
    std::function<std::string(std::string_view)> on_message;
};

void websocket_server_start(const websocket_server_config& e);
