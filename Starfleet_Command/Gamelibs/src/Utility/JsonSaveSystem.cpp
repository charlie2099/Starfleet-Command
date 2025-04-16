#include "Utility/JsonSaveSystem.hpp"

void Chilli::JsonSaveSystem::SaveFile(const std::string &filepath, const json &data)
{
    std::ofstream file(filepath);
    if(file.is_open())
    {
        file << std::setw(4) << data << std::endl;
        file.close();
    }
}

json Chilli::JsonSaveSystem::LoadFile(const std::string &filepath)
{
    json data;
    std::ifstream file(filepath);

    if(file.is_open())
    {
        try
        {
            file >> data;  // Actually parse the JSON from the file
            file.close();
        }
        catch(const json::parse_error& e)
        {
            std::cerr << "JSON parse error: " << e.what() << std::endl;
            // Return empty JSON object on error
        }
    }
    else
    {
        std::cerr << "Could not open file: " << filepath << std::endl;
    }

    return data;  // Return data, empty or filled
}

bool Chilli::JsonSaveSystem::CheckFileExists(const std::string &filepath)
{
    std::ifstream file(filepath);
    bool fileExists = file.good();
    file.close();
    return fileExists;
}
