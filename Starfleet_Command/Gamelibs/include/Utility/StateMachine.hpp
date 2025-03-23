#ifndef STARFLEET_COMMAND_STATEMACHINE_HPP
#define STARFLEET_COMMAND_STATEMACHINE_HPP
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <SFML/System/Time.hpp>

class IState
{
public:
    virtual void OnStateEnter() = 0;
    virtual void OnStateUpdate(sf::Time deltaTime) = 0;
    virtual void OnStateExit() = 0;
};

class StateMachine
{
public:
    void Update(sf::Time deltaTime);

    void SetStates(std::unordered_map<std::type_index, std::shared_ptr<IState>> statesDict);
    void ChangeState(std::type_index newState);
    std::shared_ptr<IState>& GetCurrentState() { return _currentState; }

private:
    std::shared_ptr<IState> _currentState;
    std::unordered_map<std::type_index, std::shared_ptr<IState>> _availableStates {};
};

#endif //STARFLEET_COMMAND_STATEMACHINE_HPP
