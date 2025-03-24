#ifndef STARFLEET_COMMAND_AIDIRECTOR_HPP
#define STARFLEET_COMMAND_AIDIRECTOR_HPP
#include "DirectorIntensityCalculator.hpp"
#include "Utility/StateMachine.hpp"
#include "AIDirector/DirectorBuildUpState.hpp"
#include "AIDirector/DirectorPeakState.hpp"
#include "AIDirector/DirectorPeakFadeState.hpp"
#include "AIDirector/DirectorRespiteState.hpp"
#include "Sprites/Player/Player.hpp"
#include "Sprites/Enemy/Enemy.hpp"

class AiDirector
{
public:
    //static AiDirector Instance;

    AiDirector(Player& player, Enemy& enemy);

    void Update(sf::Time deltaTime);

    enum DirectorTempoState
    {
        BuildUp,
        Peak,
        PeakFade,
        Respite
    };

    void IncreasePerceivedIntensity(sf::Time deltaTime);
    void DecreasePerceivedIntensity(sf::Time deltaTime);

    float GetPerceivedIntensity() const  { return _perceivedIntensity; }
    float GetPeakIntensityThreshold() const { return PEAK_INTENSITY_MAX; }
    float GetEnemyMothershipHealth() { return _enemy.GetMothership()->GetHealth(); }

private:
    std::unique_ptr<DirectorIntensityCalculator> _intensityCalculator;
    StateMachine _stateMachine;
    Player& _player;
    Enemy& _enemy;
    float _perceivedIntensity = 0;
    float _peakDuration = 5.0F;
    float _respiteDuration = 10.0F;
    const float PEAK_INTENSITY_MAX = 100.0F;
};

#endif //STARFLEET_COMMAND_AIDIRECTOR_HPP
