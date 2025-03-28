#include "StarshipDeploymentManager.hpp"

StarshipDeploymentManager::StarshipDeploymentManager(int maxQueueSize, sf::Color deploymentBarColour)
{
    _maxQueueSize = maxQueueSize;
    _starshipDeploymentBar.SetColour(deploymentBarColour);
    _starshipQueueBoxTexture.loadFromFile("Resources/Textures/starfleet_selection_crosshairs.png");

    for (int i = 0; i < _maxQueueSize; ++i)
    {
        _starshipQueueBoxSprites[i].setTexture(_starshipQueueBoxTexture);
        _starshipQueueBoxSprites[i].setScale(0.09F, 0.09F);
        _starshipQueueBoxSprites[i].setColor(deploymentBarColour);
    }

    _starshipQueueBoxIconTexture.loadFromFile("Resources/Textures/square.png");
}

void StarshipDeploymentManager::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    _starshipDeploymentBar.SetPosition(_deploymentBarPosition);
    _starshipDeploymentBar.Update(window, deltaTime);

    for (int i = 0; i < _maxQueueSize; ++i)
    {
        _starshipQueueBoxSprites[i].setPosition(_starshipDeploymentBar.GetOuterPos().x + _starshipDeploymentBar.GetSize().width - _starshipQueueBoxSprites[i].getGlobalBounds().width - (i * (_starshipQueueBoxSprites[i].getGlobalBounds().width + 5.0F)), _starshipDeploymentBar.GetOuterPos().y + _starshipQueueBoxSprites[i].getGlobalBounds().height + 5.0F);
    }

    for (int i = 0; i < _starshipQueueBoxIconSprites.size(); ++i)
    {
        _starshipQueueBoxIconSprites[i].setPosition(
                _starshipQueueBoxSprites[i].getPosition().x + _starshipQueueBoxSprites[i].getGlobalBounds().width/2.0F - _starshipQueueBoxIconSprites[i].getGlobalBounds().width/2.0F,
                _starshipQueueBoxSprites[i].getPosition().y + _starshipQueueBoxSprites[i].getGlobalBounds().height/2.0F - _starshipQueueBoxIconSprites[i].getGlobalBounds().height/2.0F);

        if(IsQueueFull())
        {
            _starshipQueueBoxIconSprites[i].setColor(_predefinedColours.LIGHTORANGE);
        }

        _starshipQueueBoxIconSprites[i].setColor(IsQueueFull() ? _predefinedColours.LIGHTORANGE : _starshipQueueBoxSprites[0].getColor());
    }
}

void StarshipDeploymentManager::Render(sf::RenderWindow &window)
{
    _starshipDeploymentBar.Render(window);

    if(not _starshipDeploymentBar.InProgress())
        return;

    for (int i = 0; i < _maxQueueSize; ++i)
    {
        window.draw(_starshipQueueBoxSprites[i]);
    }

    for (int i = 0; i < _starshipQueueBoxIconSprites.size(); ++i)
    {
        window.draw(_starshipQueueBoxIconSprites[i]);
    }
}

void StarshipDeploymentManager::AddStarshipToQueue(StarshipFactory::STARSHIP_TYPE starshipType, int selectedSpacelane)
{
    _starshipTypeDeploymentQueue.push(starshipType);
    _spacelaneStarshipDeploymentQueue.push(selectedSpacelane);
    auto& newQueueBoxIconSprite = _starshipQueueBoxIconSprites.emplace_back();
    newQueueBoxIconSprite.setTexture(_starshipQueueBoxIconTexture);
    newQueueBoxIconSprite.setScale(0.09F, 0.09F);
    newQueueBoxIconSprite.setColor(_starshipQueueBoxSprites[0].getColor());
}

void StarshipDeploymentManager::RemoveFirstStarshipInQueue()
{
    _starshipTypeDeploymentQueue.pop();
    _spacelaneStarshipDeploymentQueue.pop();
    _starshipQueueBoxIconSprites.erase(_starshipQueueBoxIconSprites.begin());
}

void StarshipDeploymentManager::ResetDeploymentBar()
{
    _starshipDeploymentBar.ResetProgressBar();
}

void StarshipDeploymentManager::SetDeploymentBarPos(sf::Vector2<float> pos)
{
    _deploymentBarPosition = pos;
}

void StarshipDeploymentManager::SetDeploymentBarText(const std::string &text)
{
    _starshipDeploymentBar.SetProgressBarText(text);
}

void StarshipDeploymentManager::SetDeploymentTime(float time)
{
    _starshipDeploymentBar.SetTimeToCompleteTask(time);
}

void StarshipDeploymentManager::SetDeploymentStatus(bool status)
{
    _starshipDeploymentBar.SetProgressBarStatus(status);
}

void StarshipDeploymentManager::AddBasicObserver(const std::pair<ProgressBar::EventID, std::function<void()>>& observer)
{
    _starshipDeploymentBar.AddBasicObserver(observer);
}
