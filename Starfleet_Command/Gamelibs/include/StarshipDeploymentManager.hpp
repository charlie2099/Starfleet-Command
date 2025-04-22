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

    void ResetDeploymentBar();

    void SetDeploymentBarPos(sf::Vector2<float> pos);
    void SetDeploymentBarText(const std::string& text);
    void SetDeploymentBarWaitingText(const std::string& text);
    void SetDeploymentTime(float time);
    void SetDeploymentStatus(bool status);

    StarshipFactory::STARSHIP_TYPE GetNextStarshipTypeInQueue() {  return _starshipTypeDeploymentQueue.front(); }
    int GetNextSpacelaneInQueue() { return _spacelaneStarshipDeploymentQueue.front(); }
    sf::Vector2<float> GetDeploymentBarPos() { return _deploymentBarPosition; }

    bool IsCurrentlyDeploying() { return _starshipDeploymentBar.InProgress(); }
    bool IsQueueFull() { return _starshipTypeDeploymentQueue.size() >= _maxQueueSize; }
    bool IsQueueEmpty() { return _starshipTypeDeploymentQueue.empty(); }
    bool IsStarshipTypeInQueue(StarshipFactory::STARSHIP_TYPE starshipType);

    void AddBasicObserver(const std::pair<ProgressBar::EventID, std::function<void()>>& observer);

private:
    ProgressBar _starshipDeploymentBar;
    std::queue<StarshipFactory::STARSHIP_TYPE> _starshipTypeDeploymentQueue;
    std::queue<int> _spacelaneStarshipDeploymentQueue;
    sf::Vector2<float> _deploymentBarPosition;
    int _maxQueueSize = 5;

    sf::Texture _starshipQueueBoxTexture;
    std::array<sf::Sprite, 5> _starshipQueueBoxSprites; // TODO: Find a way to initialise size with max queue size variable set above
    sf::Texture _starshipQueueBoxIconTexture;
    std::vector<sf::Sprite> _starshipQueueBoxIconSprites;
};

#endif //STARFLEET_COMMAND_STARSHIPDEPLOYMENTMANAGER_HPP
