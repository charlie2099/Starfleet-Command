#ifndef STARFLEET_COMMAND_DIRECTORRESPITESTATE_HPP
#define STARFLEET_COMMAND_DIRECTORRESPITESTATE_HPP
#include "Utility/StateMachine.hpp"
#include "AIDirector/AiDirector.hpp"

class DirectorRespiteState : public IState
{
public:
    DirectorRespiteState(AiDirector& director, StateMachine& stateMachine);

    void OnStateEnter() override;
    void OnStateUpdate(sf::Time deltaTime) override;
    void OnStateExit() override;

private:
    AiDirector& _aiDirector;
    StateMachine& _stateMachine;
};

#endif //STARFLEET_COMMAND_DIRECTORRESPITESTATE_HPP
