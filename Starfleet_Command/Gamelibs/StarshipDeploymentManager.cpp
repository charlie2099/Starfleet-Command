#include "StarshipDeploymentManager.hpp"

void StarshipDeploymentManager::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    _starshipDeploymentBar.SetPosition({_deploymentBarPosition.x, _deploymentBarPosition.y - _starshipDeploymentBar.GetSize().height * 3.5F});
    _starshipDeploymentBar.Update(window, deltaTime);
}

void StarshipDeploymentManager::Render(sf::RenderWindow &window)
{
    _starshipDeploymentBar.Render(window);
}

void StarshipDeploymentManager::AddStarshipToQueue(StarshipFactory::STARSHIP_TYPE starshipType, int selectedSpacelane)
{
    _starshipTypeDeploymentQueue.push(starshipType);
    _spacelaneStarshipDeploymentQueue.push(selectedSpacelane);
}

void StarshipDeploymentManager::RemoveFirstStarshipInQueue()
{
    _starshipTypeDeploymentQueue.pop();
    _spacelaneStarshipDeploymentQueue.pop();
}

void StarshipDeploymentManager::SetDeploymentBarPos(sf::Vector2<float> pos)
{
    _deploymentBarPosition = pos;
}
