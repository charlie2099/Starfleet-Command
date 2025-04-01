#ifndef STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
#define STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
#include "AIDirector/RuleEngine/DirectorIntensityRuleEngine.hpp"
#include "AIDirector/Rules/IntensityRules/EnemyMothershipHealthLow_IntensityRule.hpp"
#include "AIDirector/Rules/IntensityRules/PlayerMothershipHealthLow_IntensityRule.hpp"
#include "AIDirector/Rules/IntensityRules/EnemyStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/Rules/IntensityRules/PlayerStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/Rules/IntensityRules/PlayerScrapSurplus_IntensityRule.hpp"
#include <memory>
#include <vector>

class AiDirector;

class DirectorIntensityCalculator
{
public:
    DirectorIntensityCalculator();
    float CalculatePerceivedIntensityOutput(AiDirector& director);

private:
    void AddRule(const std::shared_ptr<IDirectorIntensityRule>& rule);
    std::vector<std::shared_ptr<IDirectorIntensityRule>> _rules;
};

#endif //STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
