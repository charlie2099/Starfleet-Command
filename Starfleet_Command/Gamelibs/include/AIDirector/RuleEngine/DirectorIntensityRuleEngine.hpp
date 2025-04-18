#ifndef STARFLEET_COMMAND_DIRECTORINTENSITYRULEENGINE_HPP
#define STARFLEET_COMMAND_DIRECTORINTENSITYRULEENGINE_HPP
#include "AIDirector/Rules/IntensityRules/IDirectorIntensityRule.hpp"
#include <memory>
#include <vector>

class AiDirector;

class DirectorIntensityRuleEngine
{
public:
    explicit DirectorIntensityRuleEngine(const std::vector<std::shared_ptr<IDirectorIntensityRule>>& rules);
    float CalculatePerceivedIntensitySum(AiDirector& director);

private:
    std::vector<std::shared_ptr<IDirectorIntensityRule>> _rules;
};

#endif //STARFLEET_COMMAND_DIRECTORINTENSITYRULEENGINE_HPP
