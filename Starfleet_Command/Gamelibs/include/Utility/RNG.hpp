#ifndef STARFLEET_COMMAND_RNG_HPP
#define STARFLEET_COMMAND_RNG_HPP
#include <random>
#include <chrono>

class RNG
{
public:
    RNG(int min, int max);
    int GenerateNumber();

private:
    static std::mt19937 GetEngine();
    std::mt19937 _randomGenerator;
    std::uniform_int_distribution<int> _uniformIntDistribution;
};

#endif //STARFLEET_COMMAND_RNG_HPP
