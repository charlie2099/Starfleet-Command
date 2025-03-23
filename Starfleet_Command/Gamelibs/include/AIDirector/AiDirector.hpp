#ifndef STARFLEET_COMMAND_AIDIRECTOR_HPP
#define STARFLEET_COMMAND_AIDIRECTOR_HPP
#include "DirectorIntensityCalculator.hpp"
#include "Utility/StateMachine.hpp"
#include "AIDirector/DirectorBuildUpState.hpp"
#include "AIDirector/DirectorPeakState.hpp"
#include "AIDirector/DirectorPeakFadeState.hpp"
#include "AIDirector/DirectorRespiteState.hpp"
#include <SFML/System/Time.hpp>

class AiDirector
{
public:
    //static AiDirector Instance;

    AiDirector();

    void Update(sf::Time deltaTime);

    enum DirectorTempoState
    {
        BuildUp,
        Peak,
        PeakFade,
        Respite
    };

    void IncreasePerceivedIntensity(sf::Time deltaTime);
    void DecreasePerceivedIntensity();

private:
    std::unique_ptr<DirectorIntensityCalculator> _intensityCalculator;
    StateMachine _stateMachine;
    // std::vector<std::unique_ptr<IStarship>> _enemyStarships;
    float _perceivedIntensity = 0;
    float _peakDuration = 5.0F;
    float _respiteDuration = 10.0F;
};

#endif //STARFLEET_COMMAND_AIDIRECTOR_HPP
