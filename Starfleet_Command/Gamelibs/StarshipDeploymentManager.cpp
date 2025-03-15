#include "StarshipDeploymentManager.hpp"

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
