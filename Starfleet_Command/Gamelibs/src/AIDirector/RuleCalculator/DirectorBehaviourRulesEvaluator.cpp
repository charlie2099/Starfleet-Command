#include "AIDirector/RuleCalculator/DirectorBehaviourRulesEvaluator.hpp"

DirectorBehaviourRulesEvaluator::~DirectorBehaviourRulesEvaluator()
{
    _rules.clear();
}

DirectorBehaviourRulesEvaluator::DirectorBehaviourRulesEvaluator()
{
    auto rulesData = Chilli::JsonSaveSystem::LoadFile(DIRECTOR_RULES_FILE_PATH);
    if(rulesData.contains("BehaviourRules"))
    {
        auto behaviourRules = rulesData["BehaviourRules"];
        for(const auto& behaviourRule : behaviourRules)
        {
            if(behaviourRule.contains("Enabled") && behaviourRule["Enabled"] == true)
            {
                /// Parse DeployStarshipsAtStart rule
                if(behaviourRule.contains("Type") && behaviourRule["Type"] == "DeployStarshipsAtStart_BehaviourRule")
                {
                    std::string ruleID = behaviourRule["Name"];
                    int rulePriority = behaviourRule["RulePriority"];
                    int maxEnemySpawnCount = behaviourRule["MaxEnemySpawnCount"];
                    StarshipFactory::STARSHIP_TYPE starshipTypeToSpawn = StarshipFactory::GetStarshipTypeFromString(behaviourRule["StarshipTypeToSpawn"]);
                    AddRule(std::make_shared<DeployStarshipsAtStart_BehaviourRule>(maxEnemySpawnCount, starshipTypeToSpawn, ruleID, rulePriority));
                }

                /// Parse DeployRandomStarshipsPeriodically rule
                if(behaviourRule.contains("Type") && behaviourRule["Type"] == "DeployRandomStarshipsPeriodically_BehaviourRule")
                {
                    std::string ruleID = behaviourRule["Name"];
                    int rulePriority = behaviourRule["RulePriority"];
                    int behaviourUpdateChecksToWait = behaviourRule["BehaviourUpdateChecksToWaitBeforeExecution"];
                    StarshipFactory::STARSHIP_TYPE starshipTypeToSpawn = StarshipFactory::GetStarshipTypeFromString(behaviourRule["StarshipTypeToSpawn"]);
                    AddRule(std::make_shared<DeployRandomStarshipsPeriodically_BehaviourRule>(starshipTypeToSpawn, behaviourUpdateChecksToWait, ruleID, rulePriority));
                }

                /// Parse PlayerSpacelaneDominance rule
                if(behaviourRule.contains("Type") && behaviourRule["Type"] == "PlayerSpacelaneDominance_BehaviourRule")
                {
                    std::string ruleID = behaviourRule["Name"];
                    int rulePriority = behaviourRule["RulePriority"];
                    int maxPlayerStarshipsInLane = behaviourRule["MaxPlayerStarshipsInLane"];
                    AddRule(std::make_shared<PlayerSpacelaneDominance_BehaviourRule>(maxPlayerStarshipsInLane, ruleID, rulePriority));
                }

                /// Parse Diversion rule
                if(behaviourRule.contains("Type") && behaviourRule["Type"] == "Diversion_BehaviourRule")
                {
                    std::string ruleID = behaviourRule["Name"];
                    int rulePriority = behaviourRule["RulePriority"];
                    StarshipFactory::STARSHIP_TYPE starshipToCounter = StarshipFactory::GetStarshipTypeFromString(behaviourRule["StarshipToCounter"]);
                    std::vector<StarshipFactory::STARSHIP_TYPE> starshipsToCounterWith;
                    for(const auto& counterStarship : behaviourRule["StarshipsToCounterWith"])
                    {
                        starshipsToCounterWith.push_back(StarshipFactory::GetStarshipTypeFromString(counterStarship));
                    }
                    AddRule(std::make_shared<Diversion_BehaviourRule>(starshipToCounter, starshipsToCounterWith, ruleID, rulePriority));
                }

                /// Parse CounterAttack rules
                if(behaviourRule.contains("Type") && behaviourRule["Type"] == "CounterAttack_BehaviourRule")
                {
                    std::string ruleID = behaviourRule["Name"];
                    int rulePriority = behaviourRule["RulePriority"];
                    StarshipFactory::STARSHIP_TYPE starshipToCounter = StarshipFactory::GetStarshipTypeFromString(behaviourRule["StarshipToCounter"]);
                    std::vector<StarshipFactory::STARSHIP_TYPE> starshipsToCounterWith;
                    for(const auto& counterStarship : behaviourRule["StarshipsToCounterWith"])
                    {
                        starshipsToCounterWith.push_back(StarshipFactory::GetStarshipTypeFromString(counterStarship));
                    }
                    AddRule(std::make_shared<CounterAttack_BehaviourRule>(starshipToCounter, starshipsToCounterWith, ruleID, rulePriority));
                }
            }
        }
    }

    _behaviourRuleEngine = std::make_unique<DirectorBehaviourRuleEngine>(_rules);
}

void DirectorBehaviourRulesEvaluator::EvaluateBehaviourOutput(AiDirector &director)
{
    _behaviourRuleEngine->EvaluateBehaviourOutput(director);
}

void DirectorBehaviourRulesEvaluator::AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule)
{
    _rules.push_back(rule);
}
