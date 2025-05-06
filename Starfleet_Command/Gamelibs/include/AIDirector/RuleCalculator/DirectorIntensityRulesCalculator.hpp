#ifndef STARFLEET_COMMAND_DIRECTORINTENSITYRULESCALCULATOR_HPP
#define STARFLEET_COMMAND_DIRECTORINTENSITYRULESCALCULATOR_HPP
#include "AIDirector/RuleEngine/DirectorIntensityRuleEngine.hpp"
#include "AIDirector/Rules/IntensityRules/EnemyMothershipHealthLow_IntensityRule.hpp"
#include "AIDirector/Rules/IntensityRules/PlayerMothershipHealthLow_IntensityRule.hpp"
#include "AIDirector/Rules/IntensityRules/EnemyStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/Rules/IntensityRules/PlayerStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/Rules/IntensityRules/PlayerScrapSurplus_IntensityRule.hpp"
#include "Utility/JsonSaveSystem.hpp"
#include <memory>
#include <vector>

class AiDirector;

class DirectorIntensityRulesCalculator
{
public:
    DirectorIntensityRulesCalculator();
    float CalculatePerceivedIntensityOutput(AiDirector& director);

private:
    void AddRule(const std::shared_ptr<IDirectorIntensityRule>& rule);
    std::vector<std::shared_ptr<IDirectorIntensityRule>> _rules;

    const std::string DATA_DIR_PATH = "Resources/Data/";
    const std::string DIRECTOR_RULES_FILE_PATH = (DATA_DIR_PATH + "DirectorRules.json");
};

#endif //STARFLEET_COMMAND_DIRECTORINTENSITYRULESCALCULATOR_HPP
