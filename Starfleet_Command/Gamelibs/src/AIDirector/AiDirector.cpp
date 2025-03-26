#include "AIDirector/AiDirector.hpp"

AiDirector::AiDirector(Player& player, Enemy& enemy, std::vector<std::unique_ptr<SpaceLane>>& spacelanes)
: _player(player), _enemy(enemy), _spacelanes(spacelanes), _intensityCalculator(std::make_unique<DirectorIntensityCalculator>()), _behaviourCalculator(std::make_unique<DirectorBehaviourCalculator>())
{
    std::unordered_map<std::type_index, std::shared_ptr<IState>> cachedStates =
    {
            { typeid(DirectorBuildUpState), std::make_shared<DirectorBuildUpState>(*this, _stateMachine) },
            { typeid(DirectorPeakState), std::make_shared<DirectorPeakState>(*this, _stateMachine) },
            { typeid(DirectorPeakFadeState), std::make_shared<DirectorPeakFadeState>(*this, _stateMachine) },
            { typeid(DirectorRespiteState), std::make_shared<DirectorRespiteState>(*this, _stateMachine) }
    };
    _stateMachine.SetStates(cachedStates);
    _stateMachine.ChangeState(typeid(DirectorBuildUpState));

    // TODO: Subscribe to StateMachine OnStateChanged event and call behaviourCalculator.ApplyBehaviourOutput()

    DirectorEventBus::Subscribe(DirectorEventBus::DirectorEvent::EnteredNewState, [this]() { PerformBehaviour(); });

    /*for (int i = 0; i < _starshipTemplateToBeDeployed.size(); ++i)
    {
        _starshipTemplateToBeDeployed[i] = StarshipFactory::CreateShip(static_cast<StarshipFactory::STARSHIP_TYPE>(i), 0);
    }*/
}

void AiDirector::Update(sf::Time deltaTime)
{
    _stateMachine.Update(deltaTime);

    /*if(not _enemyStarshipDeploymentQueue.first.empty())
    {
        for (int i = 0; i < _enemyStarshipDeploymentQueue.first.size(); ++i)
        {
            _deploymentTimer = _starshipTemplateToBeDeployed[_enemyStarshipDeploymentQueue.first.front()]->GetDeploymentSpeed() *

            if(_gameClock.getElapsedTime().asSeconds() <= _starshipTemplateToBeDeployed[_enemyStarshipDeploymentQueue.first.front()]->GetDeploymentSpeed())
            {
                auto queuedStarshipType = StarshipFactory::STARSHIP_TYPE(_enemyStarshipDeploymentQueue.first.front());
                auto queuedSpacelane = _enemyStarshipDeploymentQueue.second.front();
                _enemy.CreateStarship(queuedStarshipType, queuedSpacelane);

                auto& newestStarship = _enemy.GetStarships()[_enemy.GetStarshipCount() - 1];
                _enemy.SetStarshipPosition(newestStarship, {_spacelanes[queuedSpacelane]->GetPos().x + _spacelanes[queuedSpacelane]->GetSize().x, _spacelanes[queuedSpacelane]->GetPos().y + _spacelanes[queuedSpacelane]->GetSize().y / 2.0F});
                _enemy.SetStarshipRotation(newestStarship, 180);

                _enemyStarshipDeploymentQueue.first.pop();
                _enemyStarshipDeploymentQueue.second.pop();

                _deploymentTimer
            }
        }
    }*/
}

void AiDirector::SpawnEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane)
{
    _enemy.CreateStarship(starshipType, spawnLane);
    _enemy.SetStarshipPosition(_enemy.GetStarships()[_enemy.GetStarshipCount() - 1], {_spacelanes[spawnLane]->GetPos().x + _spacelanes[spawnLane]->GetSize().x, _spacelanes[spawnLane]->GetPos().y + _spacelanes[spawnLane]->GetSize().y / 2.0F});
    _enemy.SetStarshipRotation(_enemy.GetStarships()[_enemy.GetStarshipCount() - 1], 180);
    // TODO: Deduct scrap metal cost OR invoke event saying a ship has spawned and have the scrap metal manager listen out for that?
    /*_enemyScrapMetalManager->SpendScrap(newestEnemyStarship->GetBuildCost());
    _enemyScrapMetalManager->SetScrapText("Scrap Metal: " + std::to_string(_enemyScrapMetalManager->GetCurrentScrapMetalAmount()));*/

}

void AiDirector::QueueEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane)
{
    //_enemyStarshipDeploymentQueue.first.push(starshipType);
    //_enemyStarshipDeploymentQueue.second.push(spawnLane);
}

void AiDirector::IncreasePerceivedIntensity(sf::Time deltaTime)
{
    float intensity = _intensityCalculator->CalculatePerceivedIntensityOutput(*this);
    _perceivedIntensity += intensity * deltaTime.asSeconds();

    if(_perceivedIntensity >= 100)
    {
        _perceivedIntensity = 100;
    }
}

void AiDirector::DecreasePerceivedIntensity(sf::Time deltaTime)
{
    float intensity = _intensityCalculator->CalculatePerceivedIntensityOutput(*this);
    _perceivedIntensity -= intensity * deltaTime.asSeconds();

    if(_perceivedIntensity <= 0)
    {
        _perceivedIntensity = 0;
    }
}

void AiDirector::PerformBehaviour()
{
    std::cout << "Applying Behaviour Output" << std::endl;
    _behaviourCalculator->ApplyBehaviourOutput(*this);
}
