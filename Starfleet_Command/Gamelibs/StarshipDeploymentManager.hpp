#ifndef STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
#define STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
#include "Sprites/Starships/StarshipFactory.hpp"
#include "Sprites/UI/ProgressBar.hpp"
#include <queue>

class StarshipDeploymentManager
{
public:
    StarshipDeploymentManager(int maxQueueSize, sf::Color deploymentBarColour);
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
    bool IsQueueFull() { return _starshipTypeDeploymentQueue.size() >= _maxQueueSize; }
    bool IsQueueEmpty() { return _starshipTypeDeploymentQueue.empty(); }

    //void AddBasicObserver();

private:
    ProgressBar _starshipDeploymentBar;
    std::queue<StarshipFactory::STARSHIP_TYPE> _starshipTypeDeploymentQueue;
    std::queue<int> _spacelaneStarshipDeploymentQueue;
    sf::Vector2<float> _deploymentBarPosition;
    int _maxQueueSize = 5;
    Chilli::PredefinedColours _predefinedColours;

    sf::Texture _starshipQueueBoxTexture;
    std::array<sf::Sprite, 5> _starshipQueueBoxSprites; // TODO: Find a way to initialise size with max queue size variable set above
    sf::Texture _starshipQueueBoxIconTexture;
    std::vector<sf::Sprite> _starshipQueueBoxIconSprites;
};

#endif //STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
