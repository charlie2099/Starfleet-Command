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
                /// Parse SpawnWeakStarshipsAtStart rule
                if(behaviourRule.contains("Type") && behaviourRule["Type"] == "SpawnWeakStarshipsAtStart_BehaviourRule")
                {
                    std::string ruleID = behaviourRule["Name"];
                    int rulePriority = behaviourRule["RulePriority"];
                    float timePassedUntilSpawn = behaviourRule["TimePassedUntilSpawn"];
                    int maxEnemySpawnCount = behaviourRule["MaxEnemySpawnCount"];
                    AddRule(std::make_shared<SpawnWeakStarshipsAtStart_BehaviourRule>(timePassedUntilSpawn, maxEnemySpawnCount, ruleID, rulePriority));
                }

                /// Parse PlayerSpacelaneDominance rule
                if(behaviourRule.contains("Type") && behaviourRule["Type"] == "PlayerSpacelaneDominance_BehaviourRule")
                {
                    std::string ruleID = behaviourRule["Name"];
                    int rulePriority = behaviourRule["RulePriority"];
                    int maxPlayerStarshipsInLane = behaviourRule["MaxPlayerStarshipsInLane"];
                    int maxSpawnAmount = behaviourRule["MaxSpawnAmount"];
                    AddRule(std::make_shared<PlayerSpacelaneDominance_BehaviourRule>(maxPlayerStarshipsInLane, maxSpawnAmount, ruleID, rulePriority));
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
            //std::cout << behaviourRule["Name"] << ": " << behaviourRule["Enabled"] << std::endl;
        }
    }
}

void DirectorBehaviourRulesEvaluator::EvaluateBehaviourOutput(AiDirector &director)
{
    //DirectorBehaviourRuleEngine engine((std::vector<std::shared_ptr<IDirectorBehaviourRule>>(_rules)));
    DirectorBehaviourRuleEngine engine(_rules);
    engine.EvaluateBehaviourOutput(director);
}

void DirectorBehaviourRulesEvaluator::AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule)
{
    _rules.push_back(rule);
}
