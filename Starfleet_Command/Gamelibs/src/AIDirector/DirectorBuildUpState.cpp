#include "AIDirector/DirectorBuildUpState.hpp"
#include <iostream>

DirectorBuildUpState::DirectorBuildUpState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorBuildUpState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredBuildUpState);
    std::cout << "BUILD UP STATE" << std::endl;
}

void DirectorBuildUpState::OnStateUpdate(sf::Time deltaTime)
{
    _aiDirector.IncreasePerceivedIntensity(deltaTime);
}

void DirectorBuildUpState::OnStateExit() {}