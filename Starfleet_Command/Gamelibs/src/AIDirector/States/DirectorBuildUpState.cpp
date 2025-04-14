#include "AIDirector/States/DirectorBuildUpState.hpp"

DirectorBuildUpState::DirectorBuildUpState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorBuildUpState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredBuildUpState);
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredNewState);
    // TODO: Call or perform BuildUp state specific behaviour here?
    //_aiDirector.DoSomething_OnDirectorStateChange();
    //_aiDirector.QueueEnemy()
}

void DirectorBuildUpState::OnStateUpdate(sf::Time deltaTime)
{
    _aiDirector.UpdatePerceivedIntensity(deltaTime);

    if(_aiDirector.GetPerceivedIntensity() >= _aiDirector.GetPeakIntensityThreshold())
    {
        // TODO: Set enemy spawn count to max
        _stateMachine.ChangeState(typeid(DirectorPeakState));
    }
}

void DirectorBuildUpState::OnStateExit()
{
    DirectorEventBus::Publish(DirectorEventBus::ReachedPeakIntensity);
}