#include "AIDirector/States/DirectorPeakFadeState.hpp"

DirectorPeakFadeState::DirectorPeakFadeState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorPeakFadeState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredPeakFadeState);
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredNewState);
    _aiDirector.SetMaxEnemyPopulation(5);
}

void DirectorPeakFadeState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorPeakFadeState::OnStateExit() {}