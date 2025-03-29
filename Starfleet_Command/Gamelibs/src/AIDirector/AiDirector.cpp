#include "AIDirector/AiDirector.hpp"

AiDirector::AiDirector(Player& player, Enemy& enemy, std::vector<std::unique_ptr<SpaceLane>>& spacelanes, sf::View &displayView)
: _player(player), _enemy(enemy), _spacelanes(spacelanes), _displayView(displayView), _intensityCalculator(std::make_unique<DirectorIntensityCalculator>()), _behaviourCalculator(std::make_unique<DirectorBehaviourCalculator>())
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

    // TODO: Subscribe to StateMachine OnStateChanged event and call behaviourCalculator.ApplyBehaviourOutput()?

    DirectorEventBus::Subscribe(DirectorEventBus::DirectorEvent::EnteredNewState, [this]() { PerformBehaviour(); });

    _starshipDeploymentManager = std::make_unique<StarshipDeploymentManager>(5/*STARSHIP_MAX_QUEUE_SIZE*/, _enemy.GetMothership()->GetColour());

    /// Observer to starship deployment bar event
    auto starshipDeploymentBarCallback = [this] { SpawnEnemy(); };
    _starshipDeploymentManager->AddBasicObserver({ProgressBar::EventID::TASK_COMPLETED, starshipDeploymentBarCallback});

    for (int i = 0; i < _starshipTemplateToBeDeployed.size(); ++i)
    {
        _starshipTemplateToBeDeployed[i] = StarshipFactory::CreateShip(static_cast<StarshipFactory::STARSHIP_TYPE>(i), 0);
    }
}

void AiDirector::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    _stateMachine.Update(deltaTime);

    _starshipDeploymentManager->SetDeploymentBarPos({_displayView.getCenter().x + 272.0F, _displayView.getCenter().y + 312.5F}); // TODO: Use a setter method to set this relative to the enemy mothership health bar and player deployment bar position
    _starshipDeploymentManager->Update(window, deltaTime);
}

void AiDirector::Render(sf::RenderWindow &window)
{
    _starshipDeploymentManager->Render(window);
}

void AiDirector::SpawnEnemy()
{
    // TODO: Deduct scrap metal cost OR invoke event saying a ship has spawned and have the scrap metal manager listen out for that?
    /*_enemyScrapMetalManager->SpendScrap(newestEnemyStarship->GetBuildCost());
    _enemyScrapMetalManager->SetScrapText("Scrap Metal: " + std::to_string(_enemyScrapMetalManager->GetCurrentScrapMetalAmount()));*/

    std::cout << "SPAWN ENEMY" << std::endl;

    auto queuedStarship = _starshipDeploymentManager->GetNextStarshipTypeInQueue();
    auto spawnLane = _starshipDeploymentManager->GetNextSpacelaneInQueue();

    _enemy.CreateStarship(queuedStarship, spawnLane);
    _enemy.SetStarshipPosition(_enemy.GetStarships()[_enemy.GetStarshipCount() - 1], {_spacelanes[spawnLane]->GetPos().x + _spacelanes[spawnLane]->GetSize().x, _spacelanes[spawnLane]->GetPos().y + _spacelanes[spawnLane]->GetSize().y / 2.0F});
    _enemy.SetStarshipRotation(_enemy.GetStarships()[_enemy.GetStarshipCount() - 1], 180);

    _starshipDeploymentManager->RemoveFirstStarshipInQueue();
    _starshipDeploymentManager->ResetDeploymentBar();

    if(not _starshipDeploymentManager->IsQueueEmpty())
    {
        _starshipDeploymentManager->SetDeploymentBarText("Deploying " + _starshipTemplateToBeDeployed[queuedStarship]->GetStarshipName());
        _starshipDeploymentManager->SetDeploymentTime(_starshipTemplateToBeDeployed[queuedStarship]->GetDeploymentTime());
        _starshipDeploymentManager->SetDeploymentStatus(true);
    }
}

void AiDirector::QueueEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane)
{
    _starshipDeploymentManager->AddStarshipToQueue(starshipType, spawnLane);

    _starshipDeploymentManager->SetDeploymentBarText("Deploying " + _starshipTemplateToBeDeployed[starshipType]->GetStarshipName());
    _starshipDeploymentManager->SetDeploymentTime(_starshipTemplateToBeDeployed[starshipType]->GetDeploymentTime());
    _starshipDeploymentManager->SetDeploymentStatus(true);
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

