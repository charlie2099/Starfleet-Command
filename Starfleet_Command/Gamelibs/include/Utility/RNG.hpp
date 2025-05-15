#ifndef STARFLEET_COMMAND_RNG_HPP
#define STARFLEET_COMMAND_RNG_HPP
#include "Utility/JsonSaveSystem.hpp"
#include <random>
#include <chrono>

class RNG
{
public:
    enum RollQuality
    {
        PERFECT_ROLL,
        COMMON_ROLL,
        POOR_ROLL
    };

    RNG();
    RNG(int min, int max);
    int GenerateNumber();
    RollQuality GenerateRandomRoll();

private:
    static std::mt19937 GetEngine();
    std::mt19937 _randomGenerator;
    std::uniform_int_distribution<int> _uniformIntDistribution;
    std::uniform_real_distribution<double> _uniformRealDistribution;
    double _perfectRollChance = 0.10; // 10%
    double _commonRollChance = 0.60; // 60%
    //const double POOR_ROLL_CHANCE = 1.00 - (_perfectRollChance + _commonRollChance); // 30%
    double _perfectRollThreshold = _perfectRollChance;
    double _commonRollThreshold = _perfectRollChance + _commonRollChance;

    const std::string DATA_DIR_PATH = "Resources/Data/";
    const std::string RNG_DATA_PATH = (DATA_DIR_PATH + "RNGData.json");
};

#endif //STARFLEET_COMMAND_RNG_HPP
