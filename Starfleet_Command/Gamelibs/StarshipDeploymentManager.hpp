#ifndef STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
#define STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
#include "Sprites/Starships/StarshipFactory.hpp"
#include <queue>

class StarshipDeploymentManager
{
public:
    StarshipDeploymentManager() = default;
    ~StarshipDeploymentManager() = default;

    void AddStarshipToQueue(StarshipFactory::STARSHIP_TYPE starshipType, int selectedSpacelane);
    void RemoveFirstStarshipInQueue();

    StarshipFactory::STARSHIP_TYPE GetNextStarshipTypeInQueue() {  return _starshipTypeDeploymentQueue.front(); }
    int GetNextSpacelaneInQueue() { return _spacelaneStarshipDeploymentQueue.front(); }

    bool IsQueueEmpty() { return _starshipTypeDeploymentQueue.empty(); }

private:
    std::queue<StarshipFactory::STARSHIP_TYPE> _starshipTypeDeploymentQueue;
    std::queue<int> _spacelaneStarshipDeploymentQueue;
};

#endif //STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
