#ifndef STARFLEET_COMMAND_AIDIRECTOR_HPP
#define STARFLEET_COMMAND_AIDIRECTOR_HPP
#include "AIDirector/RuleCalculator/DirectorIntensityCalculator.hpp"
#include "AIDirector/RuleCalculator/DirectorBehaviourCalculator.hpp"
#include "Utility/StateMachine.hpp"
#include "AIDirector/States/DirectorBuildUpState.hpp"
#include "AIDirector/States/DirectorPeakState.hpp"
#include "AIDirector/States/DirectorPeakFadeState.hpp"
#include "AIDirector/States/DirectorRespiteState.hpp"
#include "Sprites/Player/Player.hpp"
#include "Sprites/Enemy/Enemy.hpp"
#include "SpaceLane.hpp"
#include <queue>

class AiDirector
{
public:
    //static AiDirector Instance;

    AiDirector(Player& player, Enemy& enemy, std::vector<std::unique_ptr<SpaceLane>>& spacelanes);
    void Update(sf::Time deltaTime);

    void SpawnEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane);
    void QueueEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane);
    void IncreasePerceivedIntensity(sf::Time deltaTime);
    void DecreasePerceivedIntensity(sf::Time deltaTime);
    void PerformBehaviour();

    float GetPerceivedIntensity() const  { return _perceivedIntensity; }
    float GetPeakIntensityThreshold() const { return PEAK_INTENSITY_MAX; }
    float GetPlayerMothershipHealth() { return _player.GetMothership()->GetHealth(); }
    float GetEnemyMothershipHealth() { return _enemy.GetMothership()->GetHealth(); }
    float GetElapsedGameTime() { return _gameClock.getElapsedTime().asSeconds(); }

private:
    std::unique_ptr<DirectorIntensityCalculator> _intensityCalculator;
    std::unique_ptr<DirectorBehaviourCalculator> _behaviourCalculator;
    StateMachine _stateMachine;
    Player& _player;
    Enemy& _enemy;
    std::vector<std::unique_ptr<SpaceLane>>& _spacelanes;
    //std::pair< std::queue<int>,  std::queue<int>> _enemyStarshipDeploymentQueue;
    //std::array<std::unique_ptr<IStarship>, StarshipFactory::ENUM_COUNT-2> _starshipTemplateToBeDeployed;
    sf::Clock _gameClock;
    //float _deploymentTimer = 0;
    float _perceivedIntensity = 0;
    const float PEAK_INTENSITY_MAX = 100.0F;
};

#endif //STARFLEET_COMMAND_AIDIRECTOR_HPP
