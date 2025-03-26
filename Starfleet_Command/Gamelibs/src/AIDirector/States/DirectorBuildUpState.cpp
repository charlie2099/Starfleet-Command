#include "AIDirector/States/DirectorBuildUpState.hpp"

DirectorBuildUpState::DirectorBuildUpState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorBuildUpState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredBuildUpState);
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredNewState);
    std::cout << "BUILD UP STATE" << std::endl;
}

void DirectorBuildUpState::OnStateUpdate(sf::Time deltaTime)
{
    _aiDirector.IncreasePerceivedIntensity(deltaTime);
    //std::cout << "Intensity: " << _aiDirector.GetPerceivedIntensity() << std::endl;

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