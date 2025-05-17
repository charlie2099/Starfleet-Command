#ifndef STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP
#include <string>

class AiDirector;

// Rules that determine when the director should perform certain behaviours/actions
class IDirectorBehaviourRule
{
public:
    virtual ~IDirectorBehaviourRule() = default;
    virtual std::string GetID() = 0;
    virtual int GetPriority() = 0;
    virtual bool IsValid(AiDirector& director) = 0;
    virtual void Execute(AiDirector& director) = 0;
};

#endif //STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP
