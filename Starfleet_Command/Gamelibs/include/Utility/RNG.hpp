#ifndef STARFLEET_COMMAND_RNG_HPP
#define STARFLEET_COMMAND_RNG_HPP
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
    const double PERFECT_CHANCE = 0.10; // 10%
    const double COMMON_CHANCE = 0.60; // 60%
    const double POOR_CHANCE = 1.00 - (PERFECT_CHANCE + COMMON_CHANCE); // 30%
    const double PERFECT_THRESHOLD = PERFECT_CHANCE;
    const double COMMON_THRESHOLD = PERFECT_CHANCE + COMMON_CHANCE;
};

#endif //STARFLEET_COMMAND_RNG_HPP
