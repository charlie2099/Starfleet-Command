#include "RNG.hpp"

RNG::RNG(int min, int max)
: _randomGenerator(GetEngine()), _uniformIntDistribution(min, max) {}

int RNG::GenerateValue()
{
    return _uniformIntDistribution(_randomGenerator);
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
