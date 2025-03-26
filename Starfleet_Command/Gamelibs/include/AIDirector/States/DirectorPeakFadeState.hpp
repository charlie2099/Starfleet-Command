#ifndef STARFLEET_COMMAND_DIRECTORPEAKFADESTATE_HPP
#define STARFLEET_COMMAND_DIRECTORPEAKFADESTATE_HPP
#include "Utility/StateMachine.hpp"
#include "AIDirector/AiDirector.hpp"

class DirectorPeakFadeState : public IState
{
public:
    DirectorPeakFadeState(AiDirector& director, StateMachine& stateMachine);

    void OnStateEnter() override;
    void OnStateUpdate(sf::Time deltaTime) override;
    void OnStateExit() override;

private:
    AiDirector& _aiDirector;
    StateMachine& _stateMachine;
};

#endif //STARFLEET_COMMAND_DIRECTORPEAKFADESTATE_HPP
