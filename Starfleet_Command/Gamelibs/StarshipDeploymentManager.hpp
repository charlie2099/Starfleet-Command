#ifndef STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
#define STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
#include "Sprites/Starships/StarshipFactory.hpp"
#include "Sprites/UI/ProgressBar.hpp"
#include <queue>

class StarshipDeploymentManager
{
public:
    StarshipDeploymentManager() = default;
    ~StarshipDeploymentManager() = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void AddStarshipToQueue(StarshipFactory::STARSHIP_TYPE starshipType, int selectedSpacelane);
    void RemoveFirstStarshipInQueue();

    void SetDeploymentBarPos(sf::Vector2<float> pos);

    ProgressBar& GetDeploymentBar() { return _starshipDeploymentBar; }
    StarshipFactory::STARSHIP_TYPE GetNextStarshipTypeInQueue() {  return _starshipTypeDeploymentQueue.front(); }
    int GetNextSpacelaneInQueue() { return _spacelaneStarshipDeploymentQueue.front(); }

    bool IsCurrentlyDeploying() { return _starshipDeploymentBar.InProgress(); }
    bool IsQueueEmpty() { return _starshipTypeDeploymentQueue.empty(); }

    //void AddBasicObserver();

private:
    ProgressBar _starshipDeploymentBar;
    std::queue<StarshipFactory::STARSHIP_TYPE> _starshipTypeDeploymentQueue;
    std::queue<int> _spacelaneStarshipDeploymentQueue;
    sf::Vector2<float> _deploymentBarPosition;
};

#endif //STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
