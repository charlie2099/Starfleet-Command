#include "AIDirector/DirectorBuildUpState.hpp"
#include <iostream>

DirectorBuildUpState::DirectorBuildUpState(AiDirector& director, StateMachine& stateMachine)
        : _aiDirector(director), _stateMachine(stateMachine)
{}

void DirectorBuildUpState::OnStateEnter()
{
    DirectorEventBus::Publish(DirectorEventBus::DirectorEvent::EnteredBuildUpState);
    std::cout << "BUILD UP STATE" << std::endl;
}

void DirectorBuildUpState::OnStateUpdate(sf::Time deltaTime)
{
    _aiDirector.IncreasePerceivedIntensity(deltaTime);
    //std::cout << "Intensity: " << _aiDirector.GetPerceivedIntensity() << std::endl;

    if(_aiDirector.GetPerceivedIntensity() >= _aiDirector.GetPeakIntensityThreshold())
    {
        // aiDirector.SetMaxEnemyPopCount(aiDirector.GetMaxPeakEnemyPop());
        /*std::cout << "CHANGE STATE" << std::endl;
        std::cout << "Intensity: " << _aiDirector.GetPerceivedIntensity() << std::endl;
        std::cout << "Intensity peak threshold: " << _aiDirector.GetPeakIntensityThreshold() << std::endl;*/
        _stateMachine.ChangeState(typeid(DirectorPeakState));
    }
}

void DirectorBuildUpState::OnStateExit()
{
    DirectorEventBus::Publish(DirectorEventBus::ReachedPeakIntensity);
}