#include "AIDirector/DirectorPeakFadeState.hpp"

DirectorPeakFadeState::DirectorPeakFadeState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorPeakFadeState::OnStateEnter() {}

void DirectorPeakFadeState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorPeakFadeState::OnStateExit() {}