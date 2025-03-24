#include "AIDirector/DirectorPeakFadeState.hpp"

DirectorPeakFadeState::DirectorPeakFadeState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorPeakFadeState::OnStateEnter()
{
    std::cout << "PEAK FADE STATE" << std::endl;
}

void DirectorPeakFadeState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorPeakFadeState::OnStateExit() {}