#ifndef STARFLEET_COMMAND_DIRECTOREVENTBUS_HPP
#define STARFLEET_COMMAND_DIRECTOREVENTBUS_HPP
#include "AiDirector.hpp"
#include <functional>
#include <map>

using EventCallback = std::function<void()>;

class DirectorEventBus
{
public:
    //static DirectorEventBus Instance;

    enum DirectorEvent
    {
        EnteredNewState,
        EnteredRespiteState,
        EnteredBuildUpState,
        EnteredPeakState,
        EnteredPeakFadeState,
        ReachedPeakIntensity
    };

    static void Subscribe(DirectorEvent event, const EventCallback& callback);
    static void Unsubscribe(DirectorEvent event);
    static void Publish(DirectorEvent event);

private:
    static std::map<DirectorEvent, std::vector<EventCallback>> _subscribers;
};

#endif //STARFLEET_COMMAND_DIRECTOREVENTBUS_HPP
