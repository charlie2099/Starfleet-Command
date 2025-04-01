#ifndef STARFLEET_COMMAND_DIRECTORPEAKSTATE_HPP
#define STARFLEET_COMMAND_DIRECTORPEAKSTATE_HPP
#include "Utility/StateMachine.hpp"
#include "AIDirector/AiDirector.hpp"

class DirectorPeakState : public IState
{
public:
    DirectorPeakState(AiDirector& director, StateMachine& stateMachine);

    void OnStateEnter() override;
    void OnStateUpdate(sf::Time deltaTime) override;
    void OnStateExit() override;
    std::string GetStateName() override { return "Peak"; }

private:
    AiDirector& _aiDirector;
    StateMachine& _stateMachine;
};

#endif //STARFLEET_COMMAND_DIRECTORPEAKSTATE_HPP
