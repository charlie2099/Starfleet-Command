#include "AIDirector/DirectorPeakState.hpp"

DirectorPeakState::DirectorPeakState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorPeakState::OnStateEnter()
{
    std::cout << "PEAK STATE" << std::endl;
}

void DirectorPeakState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorPeakState::OnStateExit() {}