#include "Utility/RNG.hpp"

RNG::RNG()
: _randomGenerator(GetEngine()), _uniformRealDistribution(0.0, 1.0)
{
    auto rngData = Chilli::JsonSaveSystem::LoadFile(RNG_DATA_PATH);

    if(rngData.contains("Perfect Roll Chance"))
    {
        float perfectRollChanceData = rngData["Perfect Roll Chance"];
        _perfectRollChance = perfectRollChanceData;
        _perfectRollThreshold = _perfectRollChance;
    }
    if(rngData.contains("Common Roll Chance"))
    {
        float commonRollChanceData = rngData["Common Roll Chance"];
        _commonRollChance = commonRollChanceData;
        _commonRollThreshold = _perfectRollChance + _commonRollChance;
    }
}

RNG::RNG(int min, int max)
: _randomGenerator(GetEngine()), _uniformIntDistribution(min, max)
{}

int RNG::GenerateNumber()
{
    return _uniformIntDistribution(_randomGenerator);
}

RNG::RollQuality RNG::GenerateRandomRoll()
{
    double roll = _uniformRealDistribution(_randomGenerator);

    if(roll < _perfectRollThreshold)
    {
        std::cout << "PERFECT ROLL" << std::endl;
        return PERFECT_ROLL;
    }
    else if(roll < _commonRollThreshold)
    {
        std::cout << "COMMON ROLL" << std::endl;
        return COMMON_ROLL;
    }
    else
    {
        std::cout << "POOR ROLL" << std::endl;
        return POOR_ROLL;
    }
}

std::mt19937 RNG::GetEngine()
{
    static std::random_device rd;
    std::mt19937 generator(rd());

    // Mix the time with a random value from random_device
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time ^ rd());
    return generator;
}
