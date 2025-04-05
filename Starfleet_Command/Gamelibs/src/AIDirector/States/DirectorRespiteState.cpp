#include "AIDirector/States/DirectorRespiteState.hpp"

DirectorRespiteState::DirectorRespiteState(AiDirector& director, StateMachine& stateMachine)
: _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorRespiteState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredRespiteState);
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredNewState);
    std::cout << "RESPITE STATE" << std::endl;
}

void DirectorRespiteState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorRespiteState::OnStateExit() {}
