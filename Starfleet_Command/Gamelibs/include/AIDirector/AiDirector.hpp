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
    AiDirector(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy, std::vector<std::unique_ptr<SpaceLane>>& spacelanes, sf::View &displayView, bool isDebugOn = false);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void QueueEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane);
    void UpdatePerceivedIntensity(sf::Time deltaTime);

    float GetPerceivedIntensity() const  { return _perceivedIntensity; }
    float GetPeakIntensityThreshold() const { return PEAK_INTENSITY_MAX; }
    float GetPlayerMothershipHealth() { return _player->GetMothership()->GetHealth(); }
    float GetEnemyMothershipHealth() { return _enemy->GetMothership()->GetHealth(); }
    int GetPlayerPopulation() { return _player->GetStarshipCount(); }
    int GetEnemyPopulation() { return _enemy->GetStarshipCount(); }
    int GetPlayerScrapAmount() { return _player->GetCurrentScrapAmount(); }
    int GetEnemyScrapAmount() { return _enemy->GetCurrentScrapAmount(); }
    float GetElapsedGameTime() { return _gameClock.getElapsedTime().asSeconds(); }
    std::unique_ptr<Player>& GetPlayer() { return _player; }
    std::unique_ptr<Enemy>& GetEnemy() { return _enemy; }
    int GetSpacelaneCount() { return _spacelanes.size(); }
    int GetNumOfPlayerUnitsInSpacelane(int spacelaneIndex);
    int GetNumOfEnemyUnitsInSpacelane(int spacelaneIndex);
    int GetNumOfPlayerUnitTypesInSpacelane(int spacelaneIndex, StarshipFactory::STARSHIP_TYPE starshipType);
    int GetNumOfEnemyUnitTypesInSpacelane(int spacelaneIndex, StarshipFactory::STARSHIP_TYPE starshipType);

    bool IsQueueFull() { return _starshipDeploymentManager->IsQueueFull(); }
    bool IsQueueEmpty() { return _starshipDeploymentManager->IsQueueEmpty(); }
    bool IsEnemyStarshipTypeInQueue(StarshipFactory::STARSHIP_TYPE starshipType);
    bool IsCurrentlyDeployingEnemy() { return _starshipDeploymentManager->IsCurrentlyDeploying(); }

private:
    void UpdateDeploymentStatus_OnDeploymentBegun();
    void SpawnEnemy_OnDeploymentCompleted();
    void EvaluateBehaviourRules_OnDirectorStateChange();
    std::unique_ptr<DirectorIntensityCalculator> _intensityCalculator;
    std::unique_ptr<DirectorBehaviourCalculator> _behaviourCalculator;
    StateMachine _stateMachine;
    std::unique_ptr<Player>& _player;
    std::unique_ptr<Enemy>& _enemy;
    std::vector<std::unique_ptr<SpaceLane>>& _spacelanes;
    std::unique_ptr<StarshipDeploymentManager> _starshipDeploymentManager;
    std::array<std::unique_ptr<IStarship>, 5> _starshipTemplateToBeDeployed;
    sf::Clock _gameClock;
    float _behaviourUpdateTimer = 5.0F;
    const float BEHAVIOUR_UPDATE_RATE = 5.0F; // NOTE: Periodically runs the behaviour calculator to see if any behavioural conditions have been met TODO: pick behaviours based on priority instead?
    float _perceivedIntensity = 0;
    const float PEAK_INTENSITY_MAX = 100.0F;
    sf::View& _displayView;
    bool _isDebugOn = false;
    sf::Text _debugDirectorStateText;
    sf::Text _debugPerceivedIntensityText;
    sf::Texture _enemySpawnLaneIndicatorTexture;
    sf::Sprite _enemySpawnLaneIndicatorSprite;
    //sf::Text _enemySpawnLaneIndicatorText;
};

#endif //STARFLEET_COMMAND_AIDIRECTOR_HPP
