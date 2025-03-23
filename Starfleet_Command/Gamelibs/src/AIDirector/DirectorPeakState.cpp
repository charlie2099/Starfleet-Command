#include "AIDirector/DirectorPeakState.hpp"

DirectorPeakState::DirectorPeakState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorPeakState::OnStateEnter() {}

void DirectorPeakState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorPeakState::OnStateExit() {}