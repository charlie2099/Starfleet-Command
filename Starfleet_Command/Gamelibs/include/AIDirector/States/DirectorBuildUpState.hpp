#ifndef STARFLEET_COMMAND_DIRECTORBUILDUPSTATE_HPP
#define STARFLEET_COMMAND_DIRECTORBUILDUPSTATE_HPP
#include "Utility/StateMachine.hpp"
#include "AIDirector/DirectorEventBus.hpp"

class DirectorBuildUpState : public IState
{
public:
    DirectorBuildUpState(AiDirector& director, StateMachine& stateMachine);

    void OnStateEnter() override;
    void OnStateUpdate(sf::Time deltaTime) override;
    void OnStateExit() override;
    std::string GetStateName() override { return "BuildUp"; }


private:
    AiDirector& _aiDirector;
    StateMachine& _stateMachine;
};

#endif //STARFLEET_COMMAND_DIRECTORBUILDUPSTATE_HPP
