#include "AIDirector/DirectorRespiteState.hpp"

DirectorRespiteState::DirectorRespiteState(AiDirector& director, StateMachine& stateMachine)
: _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorRespiteState::OnStateEnter()
{
    std::cout << "RESPITE STATE" << std::endl;
}

void DirectorRespiteState::OnStateUpdate(sf::Time deltaTime) {}

void DirectorRespiteState::OnStateExit() {}
