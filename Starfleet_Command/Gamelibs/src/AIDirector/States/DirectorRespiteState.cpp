#include "AIDirector/States/DirectorRespiteState.hpp"

DirectorRespiteState::DirectorRespiteState(AiDirector& director, StateMachine& stateMachine)
: _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorRespiteState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredRespiteState);
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredNewState);
    _aiDirector.SetMaxEnemyPopulation(0);
}

void DirectorRespiteState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorRespiteState::OnStateExit() {}
