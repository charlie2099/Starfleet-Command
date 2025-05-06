#include "AIDirector/RuleCalculator/DirectorIntensityRulesCalculator.hpp"

DirectorIntensityRulesCalculator::DirectorIntensityRulesCalculator()
{
    auto rulesData = Chilli::JsonSaveSystem::LoadFile(DIRECTOR_RULES_FILE_PATH);
    if(rulesData.contains("IntensityRules"))
    {
        auto intensityRules = rulesData["IntensityRules"];
        for (const auto &intensityRule: intensityRules)
        {
            if(intensityRule.contains("Enabled") && intensityRule["Enabled"] == true)
            {
                /// POSITIVE intensity factors

                /// Parse PlayerMothershipHealthLow rule
                if(intensityRule.contains("Type") && intensityRule["Type"] == "PlayerMothershipHealthLow_IntensityRule")
                {
                    float lowHealthThreshold = intensityRule["LowHealthThreshold"];
                    int intensityRating = intensityRule["IntensityRating"];
                    AddRule(std::make_shared<PlayerMothershipHealthLow_IntensityRule>(lowHealthThreshold, intensityRating));
                }

                /// Parse EnemyStarshipsInPlay rule
                if(intensityRule.contains("Type") && intensityRule["Type"] == "EnemyStarshipsInPlay_IntensityRule")
                {
                    float intensityRating = intensityRule["IntensityRatingPerStarship"];
                    AddRule(std::make_shared<EnemyStarshipsInPlay_IntensityRule>(intensityRating));
                }

                /// Parse PlayerScrapSurplus rule
                if(intensityRule.contains("Type") && intensityRule["Type"] == "PlayerScrapSurplus_IntensityRule")
                {
                    int scrapAmount = intensityRule["ScrapAmount"];
                    float intensityRating = intensityRule["IntensityRating"];
                    AddRule(std::make_shared<PlayerScrapSurplus_IntensityRule>(scrapAmount, intensityRating));
                }
            }

            /// NEGATIVE intensity factors

            /// Parse EnemyMothershipHealthLow rule
            if(intensityRule.contains("Type") && intensityRule["Type"] == "EnemyMothershipHealthLow_IntensityRule")
            {
                float lowHealthThreshold = intensityRule["LowHealthThreshold"];
                int intensityRating = intensityRule["IntensityRating"];
                AddRule(std::make_shared<EnemyMothershipHealthLow_IntensityRule>(lowHealthThreshold, intensityRating));
            }

            /// Parse PlayerStarshipsInPlay rule
            if(intensityRule.contains("Type") && intensityRule["Type"] == "PlayerStarshipsInPlay_IntensityRule")
            {
                float intensityRating = intensityRule["IntensityRatingPerStarship"];
                AddRule(std::make_shared<PlayerStarshipsInPlay_IntensityRule>(intensityRating));
            }

            std::cout << intensityRule["Name"] << ": " << intensityRule["Enabled"] << std::endl;
        }
    }
}

float DirectorIntensityRulesCalculator::CalculatePerceivedIntensityOutput(AiDirector &director)
{
    DirectorIntensityRuleEngine engine(_rules);
    return engine.CalculatePerceivedIntensitySum(director);
}

void DirectorIntensityRulesCalculator::AddRule(const std::shared_ptr<IDirectorIntensityRule>& rule)
{
    _rules.push_back(rule);
}
