#include "StarshipDeploymentManager.hpp"

StarshipDeploymentManager::StarshipDeploymentManager(int maxQueueSize, sf::Color deploymentBarColour)
{
    _maxQueueSize = maxQueueSize;
    _starshipDeploymentBar.SetColour(deploymentBarColour);
    _starshipDeploymentBar.SetProgressBarText("Awaiting orders");
    _starshipDeploymentBar.SetProgressBarWaitingText("Awaiting orders");
    _starshipQueueBoxTexture.loadFromFile("Resources/Textures/starfleet_selection_crosshairs.png");

    for (int i = 0; i < _maxQueueSize; ++i)
    {
        _starshipQueueBoxSprites.emplace_back();
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
    }
}

void StarshipDeploymentManager::Render(sf::RenderWindow &window)
{
    _starshipDeploymentBar.Render(window);

    /*if(not _starshipDeploymentBar.InProgress())
        return;*/

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

bool StarshipDeploymentManager::IsStarshipTypeInQueue(StarshipFactory::STARSHIP_TYPE starshipType)
{
    std::queue<StarshipFactory::STARSHIP_TYPE> tempStarshipQueue = _starshipTypeDeploymentQueue;
    std::vector<StarshipFactory::STARSHIP_TYPE> starshipVector;

    while (not tempStarshipQueue.empty())
    {
        starshipVector.push_back(tempStarshipQueue.front());
        tempStarshipQueue.pop();
    }

    return std::find(starshipVector.begin(), starshipVector.end(), starshipType) != starshipVector.end();
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

void StarshipDeploymentManager::SetDeploymentBarWaitingText(const std::string &text)
{
    _starshipDeploymentBar.SetProgressBarText(text);
    _starshipDeploymentBar.SetProgressBarWaitingText(text);
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
