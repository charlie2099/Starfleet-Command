#include "Sprites/Player/Player.hpp"

Player::Player(int startingScrapAmount, sf::Color teamColour)
{
    _scrapMetalManager = std::make_unique<ScrapMetalManager>(_predefinedColours.GRAY, teamColour, startingScrapAmount);
    _teamColour = teamColour;
}

void Player::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    for (auto& ship : starship)
    {
        ship->EventHandler(window, event);
    }
}

void Player::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    _scrapMetalManager->Update(window, deltaTime);
    _scrapMetalManager->SetTextPosition(_scrapTextPos.x, _scrapTextPos.y);

    for (auto& ship : starship)
    {
        ship->Update(window, deltaTime);
    }

    for (int i = 0; i < starship.size(); i++)
    {
        if(starship[i]->GetHealthComponent().GetHealth() <= 0)
        {
            StarshipDestroyedData destroyedStarshipData;
            destroyedStarshipData.DeathLocation = starship[i]->GetPos();
            destroyedStarshipData.BuildCost = starship[i]->GetBuildCost();
            InvokeAgnosticEvent(STARSHIP_DESTROYED, destroyedStarshipData);
            starship.erase(starship.begin() + i);
        }
    }
}

void Player::Render(sf::RenderWindow &window)
{
    for (auto& ship : starship)
    {
        ship->Render(window);
    }
    _scrapMetalManager->Render(window);
}

void Player::MoveStarship(int starshipIndex, sf::Vector2<float> positionOffset)
{
    starship[starshipIndex]->Move(positionOffset.x, positionOffset.y);
}

void Player::CreateStarship(StarshipFactory::STARSHIP_TYPE starshipType, int spacelane)
{
    std::unique_ptr<IStarship> newStarship = StarshipFactory::CreateShip(starshipType, spacelane);
    newStarship->SetColour(_teamColour);
    newStarship->SetProjectileColour(_teamColour);
    starship.emplace_back(std::move(newStarship));
    InvokeBasicEvent(STARSHIP_SPAWNED);
}

void Player::CreateScrapPopup(int scrapAmount, sf::Vector2<float> pos)
{
    _scrapMetalManager->CreatePopup(scrapAmount, pos);
}

void Player::SetMothershipPosition(sf::Vector2f pos)
{
    starship[0]->SetPosition(pos);
}

void Player::SetStarshipPosition(std::unique_ptr<IStarship> &ship, sf::Vector2f pos)
{
    ship->SetPosition(pos);
}

void Player::SpendScrap(int buildCost)
{
    _scrapMetalManager->SpendScrap(buildCost);
}

void Player::CollectScrap(int scrapAmount)
{
    _scrapMetalManager->CollectScrap(scrapAmount);
}

void Player::SetScrapText(const std::string& scrapText)
{
    _scrapMetalManager->SetScrapText(scrapText);
}

void Player::SetScrapTextPosition(sf::Vector2<float> pos)
{
    _scrapTextPos = pos;
}

void Player::AddBasicObserver(BasicPlayerEvent observer)
{
    _basicObservers.insert(observer);
}

void Player::AddAgnosticObserver(AgnosticPlayerEvent observer)
{
    _agnosticObservers.insert(observer);
}

void Player::InvokeBasicEvent(EventID eventId)
{
    /// Invokes the callback function assigned to the specified event id?
    auto range = _basicObservers.equal_range(eventId);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        // subscribed method is called
        iter->second();
    }
}

void Player::InvokeAgnosticEvent(EventID eventId, const std::any& anyData)
{
    /// Invokes the callback function assigned to the specified event id?
    auto ag_range = _agnosticObservers.equal_range(eventId);
    for(auto iter = ag_range.first; iter != ag_range.second; ++iter)
    {
        /// subscribed method is called
        iter->second(anyData);
    }
}







