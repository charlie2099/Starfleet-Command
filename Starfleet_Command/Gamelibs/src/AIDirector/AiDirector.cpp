#include "AIDirector/AiDirector.hpp"

AiDirector::AiDirector()
: _intensityCalculator(std::make_unique<DirectorIntensityCalculator>())
{
    std::unordered_map<std::type_index, std::shared_ptr<IState>> cachedStates =
    {
            { typeid(DirectorBuildUpState), std::make_shared<DirectorBuildUpState>(*this, _stateMachine) },
            { typeid(DirectorPeakState), std::make_shared<DirectorPeakState>(*this, _stateMachine) },
            { typeid(DirectorPeakFadeState), std::make_shared<DirectorPeakFadeState>(*this, _stateMachine) },
            { typeid(DirectorRespiteState), std::make_shared<DirectorRespiteState>(*this, _stateMachine) }
    };
    _stateMachine.SetStates(cachedStates);
    _stateMachine.ChangeState(typeid(DirectorBuildUpState));
}

void AiDirector::Update(sf::Time deltaTime)
{
    _stateMachine.Update(deltaTime);
}

void AiDirector::IncreasePerceivedIntensity(sf::Time deltaTime)
{
    float intensity = _intensityCalculator->CalculatePerceivedIntensityOutput(*this);
    _perceivedIntensity += intensity * deltaTime.asSeconds();

    if(_perceivedIntensity > 100)
    {
        _perceivedIntensity = 100;
    }
}

void AiDirector::DecreasePerceivedIntensity()
{

}
