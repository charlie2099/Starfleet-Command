#ifndef STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP
#include <string>

class AiDirector;

/**
 * @brief Abstract interface defining a contract that all behaviour rules must inherit from.
 * @note All methods are pure virtual and must be implemented by derived classes.
 */
class IDirectorBehaviourRule
{
public:
    /**
     * @brief Checks if the rule should be applied given the current game state.
     * @param director Reference to the Ai Director instance.
     * @return true if the rule conditions are satisfied.
     */
    virtual bool IsValid(AiDirector& director) = 0;
    /**
     * @brief Performs the rule's behaviour.
     * @param director Reference to the Ai Director instance.
     * @warning This method should only be called if IsValid() returns true.
     */
    virtual void Execute(AiDirector& director) = 0;
    /**
     * @brief Returns a unique identifier for this rule; utilised to make rule tracking and debugging easier.
     * @return A unique string identifier for this rule.
     */
    virtual std::string GetID() = 0;
    /**
     * @brief Returns the execution priority of this rule.
     * When multiple rules are valid simultaneously, the Ai Director will select the rule with the highest priority.
     * @return An integer priority value (lower values = higher priority).
     */
    virtual int GetPriority() = 0;
};

#endif //STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP
