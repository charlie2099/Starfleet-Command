#ifndef STARFLEET_COMMAND_JSONSAVESYSTEM_HPP
#define STARFLEET_COMMAND_JSONSAVESYSTEM_HPP
#include <fstream>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Chilli
{
    class JsonSaveSystem
    {
    public:
        static void SaveFile(const std::string &filepath, const json &data);
        static json LoadFile(const std::string& filepath);
        static bool CheckFileExists(const std::string& filepath);
    };
}

#endif //STARFLEET_COMMAND_JSONSAVESYSTEM_HPP
