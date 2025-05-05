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
        for(const auto& rule : behaviourRules)
        {
            if(rule.contains("SpawnWeakStarshipsAtStart_BehaviourRule"))
            {
                std::string ruleStatus = rule["SpawnWeakStarshipsAtStart_BehaviourRule"];
                float timePassedUntilSpawn = rule["TimePassedUntilSpawn"];
                int maxEnemySpawnCount = rule["MaxEnemySpawnCount"];

                if(ruleStatus == "ON")
                {
                    AddRule(std::make_shared<SpawnWeakStarshipsAtStart_BehaviourRule>(timePassedUntilSpawn, maxEnemySpawnCount));
                    std::cout << "SpawnWeakStarshipsAtStart_BehaviourRule is ACTIVE" << std::endl;
                }
                else
                {
                    std::cout << "SpawnWeakStarshipsAtStart_BehaviourRule is INACTIVE" << std::endl;
                }
            }

            if(rule.contains("CounterAttack_BehaviourRule"))
            {
                std::string ruleStatus = rule["CounterAttack_BehaviourRule"];
                if(ruleStatus == "ON")
                {
                    StarshipFactory::STARSHIP_TYPE starshipToCounter = StarshipFactory::GetStarshipTypeFromString(rule["StarshipToCounter"]);

                    std::vector<StarshipFactory::STARSHIP_TYPE> starshipsToCounterWith;
                    for(const auto& counterStarship : rule["StarshipsToCounterWith"])
                    {
                        starshipsToCounterWith.push_back(StarshipFactory::GetStarshipTypeFromString(counterStarship));
                    }

                    AddRule(std::make_shared<CounterAttack_BehaviourRule>(starshipToCounter, starshipsToCounterWith));
                    std::cout << "CounterAttack_BehaviourRule is ACTIVE" << std::endl;
                }
                else
                {
                    std::cout << "CounterAttack_BehaviourRule is INACTIVE" << std::endl;
                }
            }
        }
    }

    auto starshipToCounter2 = StarshipFactory::DREADNOUGHT;
    auto counterStarships2 = std::vector<StarshipFactory::STARSHIP_TYPE> { StarshipFactory::DREADNOUGHT, StarshipFactory::SUPPORT_FRIGATE };
    AddRule(std::make_shared<CounterAttack_BehaviourRule>(starshipToCounter2, counterStarships2));

    AddRule(std::make_shared<PlayerSpacelaneDominance_BehaviourRule>(2, 1));
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
