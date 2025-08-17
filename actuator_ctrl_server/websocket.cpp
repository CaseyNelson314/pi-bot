#include <App.h>
#include "websocket.hpp"

void websocket_server_start(const websocket_server_config& conf)
{
    struct UserData
    {};

    uWS::App().ws<UserData>("/", {
        .open = [&conf](auto */*ws*/) {
            conf.on_open();
        },
        .message = [&conf](auto *ws, std::string_view msg, uWS::OpCode opCode) {
            const auto response = conf.on_message(msg);
            if (response.size())
                ws->send(response, opCode, false);
        },
        .close = [&conf](auto */*ws*/, int /*code*/, std::string_view /*message*/) {
            conf.on_close();
        }
    }).listen(conf.server_port, [&conf](auto *token) {
        conf.on_server_start(static_cast<bool>(token));
    }).run();

}
