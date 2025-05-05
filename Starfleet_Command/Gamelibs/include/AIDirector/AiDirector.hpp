#ifndef STARFLEET_COMMAND_AIDIRECTOR_HPP
#define STARFLEET_COMMAND_AIDIRECTOR_HPP
#include "AIDirector/RuleCalculator/DirectorIntensityRulesCalculator.hpp"
#include "AIDirector/RuleCalculator/DirectorBehaviourRulesEvaluator.hpp"
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

/**
 * @brief Controls game difficulty and enemy behavior based on dynamic intensity rules
 */
class AiDirector
{
public:
    AiDirector(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy, std::vector<std::unique_ptr<SpaceLane>>& spacelanes, sf::View &gameplayView, bool isDebugOn = false);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    /// Behavioural Actions
    void QueueEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane);
    void UpdatePerceivedIntensity(sf::Time deltaTime);

    /// Setters
    void SetMaxEnemyPopulation(int maxPopulation);
    void SetBehaviourUpdateRate(float seconds);

    /// Getters - Game State Info
    float GetPerceivedIntensity() const  { return _perceivedIntensity; }
    float GetPeakIntensityThreshold() const { return PEAK_INTENSITY_MAX; }
    float GetElapsedGameTime() { return _gameClock.getElapsedTime().asSeconds(); }

    /// Getters - Player State Info
    float GetPlayerMothershipHealth() { return _player->GetMothership()->GetHealth(); }
    int GetPlayerPopulation() { return _player->GetStarshipCount(); }
    int GetPlayerScrapAmount() { return _player->GetCurrentScrapAmount(); }
    std::unique_ptr<Player>& GetPlayer() { return _player; }

    /// Getters - Enemy State Info
    float GetEnemyMothershipHealth() { return _enemy->GetMothership()->GetHealth(); }
    int GetEnemyPopulation() { return _enemy->GetStarshipCount(); }
    int GetEnemyScrapAmount() { return _enemy->GetCurrentScrapAmount(); }
    std::unique_ptr<Enemy>& GetEnemy() { return _enemy; }

    /// Getters - Spacelane Info
    int GetSpacelaneCount() { return _spacelanes.size(); }
    int GetNumOfPlayerUnitsInSpacelane(int spacelaneIndex);
    int GetNumOfEnemyUnitsInSpacelane(int spacelaneIndex);
    int GetNumOfPlayerUnitTypesInSpacelane(int spacelaneIndex, StarshipFactory::STARSHIP_TYPE starshipType);
    int GetNumOfEnemyUnitTypesInSpacelane(int spacelaneIndex, StarshipFactory::STARSHIP_TYPE starshipType);

    /// Getters - Deployment Queue Status Info
    bool IsQueueFull() { return _starshipDeploymentManager->IsQueueFull(); }
    bool IsQueueEmpty() { return _starshipDeploymentManager->IsQueueEmpty(); }
    bool IsEnemyStarshipTypeInQueue(StarshipFactory::STARSHIP_TYPE starshipType);
    bool IsCurrentlyDeployingEnemy() { return _starshipDeploymentManager->IsCurrentlyDeploying(); }

private:
    void UpdateDeploymentStatus_OnDeploymentBegun();
    void SpawnEnemy_OnDeploymentCompleted();
    void DoSomething_OnDirectorStateChange();

    /// Constants
    const float PEAK_INTENSITY_MAX = 100.0F;

    std::unique_ptr<DirectorIntensityRulesCalculator> _intensityCalculator;
    std::unique_ptr<DirectorBehaviourRulesEvaluator> _behaviourCalculator;
    StateMachine _stateMachine;
    std::unique_ptr<Player>& _player;
    std::unique_ptr<Enemy>& _enemy;
    std::vector<std::unique_ptr<SpaceLane>>& _spacelanes;
    std::unique_ptr<StarshipDeploymentManager> _starshipDeploymentManager;
    std::array<std::unique_ptr<IStarship>, 5> _starshipTemplateToBeDeployed;
    sf::Clock _gameClock;
    float _behaviourUpdateRate = 5.0F;
    float _behaviourUpdateTimer = 5.0F;
    float _perceivedIntensity = 0;
    int _maxEnemyPopulation = 10;

    /// View and Debug Visualisation
    sf::View& _gameplayView;
    bool _isDebugOn = false;
    sf::Text _debugDirectorStateText;
    sf::Text _debugPerceivedIntensityText;
    sf::Text _debugDirectorBehaviourUpdateRateText;
    sf::Text _debugEnemyMaxPopulationText;
    sf::Texture _enemySpawnLaneIndicatorTexture;
    sf::Sprite _enemySpawnLaneIndicatorSprite;
    //sf::Text _enemySpawnLaneIndicatorText;
};

#endif //STARFLEET_COMMAND_AIDIRECTOR_HPP
