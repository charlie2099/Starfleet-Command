#include "AIDirector/States/DirectorPeakState.hpp"

DirectorPeakState::DirectorPeakState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorPeakState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredPeakState);
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredNewState);
    //_aiDirector.SetMaxEnemyPopulation(15);
    //_aiDirector.SetBehaviourUpdateRate(1.0F);
}

void DirectorPeakState::OnStateUpdate(sf::Time deltaTime)
{
    /*_aiDirector.UpdatePerceivedIntensity(deltaTime);

    if(_aiDirector.GetPerceivedIntensity() >= _aiDirector.GetPeakIntensityThreshold())
    {
        _stateMachine.ChangeState(typeid(DirectorPeakFadeState));
    }*/
}

void DirectorPeakState::OnStateExit() {}