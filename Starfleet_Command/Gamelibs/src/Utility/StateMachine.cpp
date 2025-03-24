#include "Utility/StateMachine.hpp"

#include <utility>

void StateMachine::Update(sf::Time deltaTime)
{
    if(_currentState == nullptr)
    {
        _currentState = _availableStates.at(_availableStates.begin()->first);
    }

    if(_currentState != nullptr)
    {
        _currentState->OnStateUpdate(deltaTime);
    }
}

void StateMachine::SetStates(std::unordered_map<std::type_index, std::shared_ptr<IState>> statesDict)
{
    _availableStates = std::move(statesDict);
}

void StateMachine::ChangeState(std::type_index newState)
{
    if(_currentState != nullptr)
    {
        _currentState->OnStateExit();
    }

    _currentState = _availableStates[newState];
    _currentState->OnStateEnter();
    // TODO: invoke state change event here
}
