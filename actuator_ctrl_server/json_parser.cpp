#include <nlohmann/json.hpp>
#include "json_parser.hpp"

using nlohmann::json;

static void from_json(const json& j, json_schema::wheel_t& self)
{
    j.at("x").get_to(self.x);
    j.at("y").get_to(self.y);
    j.at("turn").get_to(self.turn);
}

static void from_json(const json& j, json_schema::arm_t& self)
{
    j.at("axis1").get_to(self.axis1);
    j.at("axis2").get_to(self.axis2);
    j.at("axis3").get_to(self.axis3);
    j.at("axis4").get_to(self.axis4);
    j.at("axis5").get_to(self.axis5);
}

static void from_json(const json& j, json_schema& self)
{
    j.at("wheel").get_to(self.wheel);
    j.at("arm").get_to(self.arm);
}

std::optional<json_schema> parse_json(std::string_view json_string)
{
    try
    {
        json_schema parsed = json::parse(json_string).get<json_schema>();
        return parsed;
    }
    catch (...)
    {
        return std::nullopt;
    }
}
