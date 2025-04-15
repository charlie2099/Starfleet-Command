#include "AIDirector/AiDirector.hpp"

AiDirector::AiDirector(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy, std::vector<std::unique_ptr<SpaceLane>>& spacelanes, sf::View &displayView, bool isDebugOn)
: _player(player), _enemy(enemy), _spacelanes(spacelanes), _displayView(displayView), _isDebugOn(isDebugOn), _intensityCalculator(std::make_unique<DirectorIntensityRulesCalculator>()), _behaviourCalculator(std::make_unique<DirectorBehaviourRulesEvaluator>())
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

    // TODO: Subscribe to StateMachine OnStateChanged event and call behaviourCalculator.EvaluateBehaviourOutput()?
    DirectorEventBus::Subscribe(DirectorEventBus::DirectorEvent::EnteredNewState, [this]() { DoSomething_OnDirectorStateChange(); });

    _starshipDeploymentManager = std::make_unique<StarshipDeploymentManager>(5/*STARSHIP_MAX_QUEUE_SIZE*/, _enemy->GetMothership()->GetColour());
    _starshipDeploymentManager->SetDeploymentBarWaitingText("The Director is analysing...");

    /// Observer to starship deployment bar event
    auto starshipDeploymentBegunCallback = [this] { UpdateDeploymentStatus_OnDeploymentBegun(); };
    _starshipDeploymentManager->AddBasicObserver({ProgressBar::TASK_STARTED, starshipDeploymentBegunCallback});

    /// Observer to starship deployment bar event
    auto starshipDeploymentCompletedCallback = [this] { SpawnEnemy_OnDeploymentCompleted(); };
    _starshipDeploymentManager->AddBasicObserver({ProgressBar::EventID::TASK_COMPLETED, starshipDeploymentCompletedCallback});

    for (int i = 0; i < _starshipTemplateToBeDeployed.size(); ++i)
    {
        _starshipTemplateToBeDeployed[i] = StarshipFactory::CreateShip(static_cast<StarshipFactory::STARSHIP_TYPE>(i), 0);
    }

    _debugDirectorStateText.setString("Director State: " + _stateMachine.GetCurrentStateName());
    _debugDirectorStateText.setFont(Chilli::CustomFonts::GetBoldFont());
    _debugDirectorStateText.setCharacterSize(11);

    _debugPerceivedIntensityText.setString("Perceived Intensity: " + std::to_string(static_cast<int>(_perceivedIntensity)));
    _debugPerceivedIntensityText.setFont(Chilli::CustomFonts::GetBoldFont());
    _debugPerceivedIntensityText.setCharacterSize(11);

    _enemySpawnLaneIndicatorTexture.loadFromFile("Resources/Textures/left.png");
    _enemySpawnLaneIndicatorSprite.setTexture(_enemySpawnLaneIndicatorTexture);
    _enemySpawnLaneIndicatorSprite.setColor(sf::Color(253, 103, 100));

    /*_enemySpawnLaneIndicatorText.setFont(Chilli::CustomFonts::GetBoldFont());
    _enemySpawnLaneIndicatorText.setCharacterSize(7);
    _enemySpawnLaneIndicatorText.setFillColor(sf::Color::White);
    _enemySpawnLaneIndicatorText.setOutlineColor(sf::Color::Black);
    _enemySpawnLaneIndicatorText.setOutlineThickness(1.0F);*/
}

void AiDirector::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    _stateMachine.Update(deltaTime);

    _starshipDeploymentManager->SetDeploymentBarPos({_displayView.getCenter().x + 272.0F, _displayView.getCenter().y + 312.5F}); // TODO: Use a setter method to set this relative to the enemy mothership health bar and player deployment bar position
    _starshipDeploymentManager->Update(window, deltaTime);

    if(_gameClock.getElapsedTime().asSeconds() >= _behaviourUpdateTimer)
    {
        _behaviourCalculator->EvaluateBehaviourOutput(*this);
        _behaviourUpdateTimer += BEHAVIOUR_UPDATE_RATE;
    }

    if(not _starshipDeploymentManager->IsQueueEmpty())
    {
        auto endOfLanePos = _spacelanes[_starshipDeploymentManager->GetNextSpacelaneInQueue()]->GetPos().x + _spacelanes[_starshipDeploymentManager->GetNextSpacelaneInQueue()]->GetSize().x + 60.0F;
        auto xPos = 0;
        float yPos = _spacelanes[_starshipDeploymentManager->GetNextSpacelaneInQueue()]->GetCentreYPos();
        if(_displayView.getCenter().x + _displayView.getSize().x/2.0F <= endOfLanePos)
        {
            xPos = _displayView.getCenter().x + _displayView.getSize().x / 2.0F - 25.0F; // padding from right
        }
        else
        {
            xPos = _spacelanes[_starshipDeploymentManager->GetNextSpacelaneInQueue()]->GetPos().x + _spacelanes[_starshipDeploymentManager->GetNextSpacelaneInQueue()]->GetSize().x + 15.0F;
        }
        _enemySpawnLaneIndicatorSprite.setPosition(xPos, yPos);

        //_enemySpawnLaneIndicatorText.setString(_starshipTemplateToBeDeployed[_starshipDeploymentManager->GetNextStarshipTypeInQueue()]->GetStarshipAbbreviation());
        //_enemySpawnLaneIndicatorText.setPosition(_enemySpawnLaneIndicatorSprite.getPosition().x - _enemySpawnLaneIndicatorText.getGlobalBounds().width/4.0F, _enemySpawnLaneIndicatorSprite.getPosition().y - _enemySpawnLaneIndicatorText.getGlobalBounds().height/2.0F);


        float time = _gameClock.getElapsedTime().asSeconds();

        // Sine wave from 0 to 1
        float pulse = (std::sin(time * 6.0F) + 1.0F) / 2.0F; // 3.0F = speed

        sf::Uint8 alpha = static_cast<sf::Uint8>(100 + pulse * 155);

        sf::Color colour = _enemySpawnLaneIndicatorSprite.getColor();
        colour.a = alpha;
        _enemySpawnLaneIndicatorSprite.setColor(colour);

        // --- Scale (size pulsation) ---
        float scale = 0.40F + pulse * 0.10f; // 1.0 → 1.10
        _enemySpawnLaneIndicatorSprite.setScale(scale, scale);

        // Optional: make sure origin is centered so scaling pulses evenly
        sf::FloatRect bounds = _enemySpawnLaneIndicatorSprite.getLocalBounds();
        _enemySpawnLaneIndicatorSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    if(not _isDebugOn)
        return;
    _debugDirectorStateText.setPosition({_starshipDeploymentManager->GetDeploymentBarPos().x, _starshipDeploymentManager->GetDeploymentBarPos().y - 17.5F});
    _debugPerceivedIntensityText.setString("Perceived Intensity: " + std::to_string(static_cast<int>(_perceivedIntensity)));
    _debugPerceivedIntensityText.setPosition({_debugDirectorStateText.getPosition().x + _debugDirectorStateText.getGlobalBounds().width + 20.0F, _debugDirectorStateText.getPosition().y});
}

void AiDirector::Render(sf::RenderWindow &window)
{
    _starshipDeploymentManager->Render(window);

    if(_isDebugOn)
    {
        window.draw(_debugDirectorStateText);
        window.draw(_debugPerceivedIntensityText);
    }

    if(not _starshipDeploymentManager->IsQueueEmpty())
    {
        window.draw(_enemySpawnLaneIndicatorSprite);
        //window.draw(_enemySpawnLaneIndicatorText);
    }
}

void AiDirector::QueueEnemy(StarshipFactory::STARSHIP_TYPE starshipType, int spawnLane)
{
    _starshipDeploymentManager->AddStarshipToQueue(starshipType, spawnLane);
    _starshipDeploymentManager->SetDeploymentStatus(true);
}

bool AiDirector::IsEnemyStarshipTypeInQueue(StarshipFactory::STARSHIP_TYPE starshipType)
{
    return _starshipDeploymentManager->IsStarshipTypeInQueue(starshipType);
}

void AiDirector::UpdatePerceivedIntensity(sf::Time deltaTime)
{
    float intensity = _intensityCalculator->CalculatePerceivedIntensityOutput(*this);
    _perceivedIntensity += intensity * deltaTime.asSeconds();

    if(_perceivedIntensity >= PEAK_INTENSITY_MAX)
    {
        _perceivedIntensity = PEAK_INTENSITY_MAX;
    }
    if(_perceivedIntensity <= 0)
    {
        _perceivedIntensity = 0;
    }
}

void AiDirector::UpdateDeploymentStatus_OnDeploymentBegun()
{
    _starshipDeploymentManager->SetDeploymentBarText("Deploying " + _starshipTemplateToBeDeployed[_starshipDeploymentManager->GetNextStarshipTypeInQueue()]->GetStarshipName());
    _starshipDeploymentManager->SetDeploymentTime(_starshipTemplateToBeDeployed[_starshipDeploymentManager->GetNextStarshipTypeInQueue()]->GetDeploymentTime());

    _enemy->SpendScrap(_starshipTemplateToBeDeployed[_starshipDeploymentManager->GetNextStarshipTypeInQueue()]->GetBuildCost());
    _enemy->SetScrapText("Scrap Metal: " + std::to_string(_enemy->GetCurrentScrapAmount()));

    /*_enemySpawnLaneIndicatorSprite.setPosition(
            _spacelanes[_starshipDeploymentManager->GetNextSpacelaneInQueue()]->GetPos().x + _spacelanes[_starshipDeploymentManager->GetNextSpacelaneInQueue()]->GetSize().x - 10.0F,
            _spacelanes[_starshipDeploymentManager->GetNextSpacelaneInQueue()]->GetPos().y);*/
}

void AiDirector::SpawnEnemy_OnDeploymentCompleted()
{
    auto queuedStarship = _starshipDeploymentManager->GetNextStarshipTypeInQueue();
    auto spawnLane = _starshipDeploymentManager->GetNextSpacelaneInQueue();
    _enemy->CreateStarship(queuedStarship, spawnLane);
    _enemy->SetStarshipPosition(_enemy->GetStarships()[_enemy->GetStarshipCount() - 1], {_spacelanes[spawnLane]->GetPos().x + _spacelanes[spawnLane]->GetSize().x - 25.0F, _spacelanes[spawnLane]->GetPos().y + _spacelanes[spawnLane]->GetSize().y / 2.0F});
    _enemy->SetStarshipRotation(_enemy->GetStarships()[_enemy->GetStarshipCount() - 1], 180);

    _starshipDeploymentManager->RemoveFirstStarshipInQueue();
    _starshipDeploymentManager->ResetDeploymentBar();

    if(not _starshipDeploymentManager->IsQueueEmpty())
    {
        _starshipDeploymentManager->SetDeploymentStatus(true);
    }
}

void AiDirector::DoSomething_OnDirectorStateChange()
{
    //_behaviourCalculator->EvaluateBehaviourOutput(*this);
    _debugDirectorStateText.setString("Director State: " + _stateMachine.GetCurrentStateName());
}

int AiDirector::GetNumOfPlayerUnitsInSpacelane(int spacelaneIndex)
{
    auto unitsInLane = 0;
    for (int i = 1; i < _player->GetStarshipCount(); ++i)
    {
        if(_player->GetStarships()[i]->GetLaneIndex() == spacelaneIndex)
        {
            unitsInLane++;
        }
    }
    return unitsInLane;
}

int AiDirector::GetNumOfEnemyUnitsInSpacelane(int spacelaneIndex)
{
    auto unitsInLane = 0;
    for (int i = 1; i < _enemy->GetStarshipCount(); ++i)
    {
        if(_enemy->GetStarships()[i]->GetLaneIndex() == spacelaneIndex)
        {
            unitsInLane++;
        }
    }
    return unitsInLane;
}

int AiDirector::GetNumOfPlayerUnitTypesInSpacelane(int spacelaneIndex, StarshipFactory::STARSHIP_TYPE starshipType)
{
    auto unitTypesInLane = 0;
    for (int i = 1; i < _player->GetStarshipCount(); ++i)
    {
        if(_player->GetStarships()[i]->GetLaneIndex() == spacelaneIndex)
        {
            if(StarshipFactory::GetStarshipType(_player->GetStarships()[i]) == starshipType)
            {
                unitTypesInLane++;
            }
        }
    }
    return unitTypesInLane;
}

int AiDirector::GetNumOfEnemyUnitTypesInSpacelane(int spacelaneIndex, StarshipFactory::STARSHIP_TYPE starshipType)
{
    auto unitTypesInLane = 0;
    for (int i = 1; i < _enemy->GetStarshipCount(); ++i)
    {
        if(_enemy->GetStarships()[i]->GetLaneIndex() == spacelaneIndex)
        {
            if(StarshipFactory::GetStarshipType(_enemy->GetStarships()[i]) == starshipType)
            {
                unitTypesInLane++;
            }
        }
    }
    return unitTypesInLane;
}


