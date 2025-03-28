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
#include "StarshipDeploymentManager.hpp"
#include <queue>

class AiDirector
{
public:
    //static AiDirector Instance;

    AiDirector(Player& player, Enemy& enemy, std::vector<std::unique_ptr<SpaceLane>>& spacelanes);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void QueueEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane);
    void IncreasePerceivedIntensity(sf::Time deltaTime);
    void DecreasePerceivedIntensity(sf::Time deltaTime);
    void PerformBehaviour();

    float GetPerceivedIntensity() const  { return _perceivedIntensity; }
    float GetPeakIntensityThreshold() const { return PEAK_INTENSITY_MAX; }
    float GetPlayerMothershipHealth() { return _player.GetMothership()->GetHealth(); }
    float GetEnemyMothershipHealth() { return _enemy.GetMothership()->GetHealth(); }
    float GetElapsedGameTime() { return _gameClock.getElapsedTime().asSeconds(); }

    bool IsQueueEmpty() { return _starshipDeploymentManager->IsQueueEmpty(); };
    bool IsCurrentlyDeployingEnemy() { return _starshipDeploymentManager->IsCurrentlyDeploying(); };

private:
    void SpawnEnemy();
    std::unique_ptr<DirectorIntensityCalculator> _intensityCalculator;
    std::unique_ptr<DirectorBehaviourCalculator> _behaviourCalculator;
    StateMachine _stateMachine;
    Player& _player;
    Enemy& _enemy;
    std::vector<std::unique_ptr<SpaceLane>>& _spacelanes;
    std::unique_ptr<StarshipDeploymentManager> _starshipDeploymentManager;
    std::array<std::unique_ptr<IStarship>, 5> _starshipTemplateToBeDeployed;
    sf::Clock _gameClock;
    float _perceivedIntensity = 0;
    const float PEAK_INTENSITY_MAX = 100.0F;
};

#endif //STARFLEET_COMMAND_AIDIRECTOR_HPP
