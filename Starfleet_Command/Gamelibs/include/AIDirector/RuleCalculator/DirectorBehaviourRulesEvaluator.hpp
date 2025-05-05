#ifndef STARFLEET_COMMAND_DIRECTORBEHAVIOURRULESEVALUATOR_HPP
#define STARFLEET_COMMAND_DIRECTORBEHAVIOURRULESEVALUATOR_HPP
#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"
#include "AIDirector/Rules/BehaviourRules/SpawnWeakStarshipsAtStart_BehaviourRule.hpp"
#include "AIDirector/Rules/BehaviourRules/CounterAttack_BehaviourRule.hpp"
#include "AIDirector/Rules/BehaviourRules/PlayerSpacelaneDominance_BehaviourRule.hpp"
#include "Utility/JsonSaveSystem.hpp"
#include <memory>
#include <vector>

class AiDirector;

class DirectorBehaviourRulesEvaluator
{
public:
    DirectorBehaviourRulesEvaluator();
    ~DirectorBehaviourRulesEvaluator();
    void EvaluateBehaviourOutput(AiDirector& director);

private:
    void AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule);
    std::vector<std::shared_ptr<IDirectorBehaviourRule>> _rules;

    const std::string DATA_DIR_PATH = "Resources/Data/";
    const std::string DIRECTOR_RULES_FILE_PATH = (DATA_DIR_PATH + "DirectorRules.json");
};

#endif //STARFLEET_COMMAND_DIRECTORBEHAVIOURRULESEVALUATOR_HPP
