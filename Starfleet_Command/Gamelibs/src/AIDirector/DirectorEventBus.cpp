#include "AIDirector/DirectorEventBus.hpp"

// Initialize the static member variable
std::map<DirectorEventBus::DirectorEvent, std::vector<EventCallback>> DirectorEventBus::_subscribers;

void DirectorEventBus::Subscribe(DirectorEvent event, const EventCallback& callback)
{
    _subscribers[event].push_back(callback);
}

void DirectorEventBus::Unsubscribe(DirectorEvent event)
{
    auto it = _subscribers.find(event);
    if(it != _subscribers.end())
    {
        it->second.clear();
    }
}

void DirectorEventBus::Publish(DirectorEvent event)
{
    auto it = _subscribers.find(event);
    if(it != _subscribers.end())
    {
        for(const auto& callback : it->second)
        {
            callback();
        }
    }
}
