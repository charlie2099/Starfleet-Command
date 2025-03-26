#include "AIDirector/States/DirectorPeakFadeState.hpp"

DirectorPeakFadeState::DirectorPeakFadeState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorPeakFadeState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredPeakFadeState);
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredNewState);
    std::cout << "PEAK FADE STATE" << std::endl;
}

void DirectorPeakFadeState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorPeakFadeState::OnStateExit() {}