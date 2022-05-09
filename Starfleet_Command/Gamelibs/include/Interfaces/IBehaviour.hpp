#ifndef STARFLEET_COMMAND_IBEHAVIOUR_HPP
#define STARFLEET_COMMAND_IBEHAVIOUR_HPP

class IBehaviour
{
public:
    virtual void Default() = 0;
    virtual void Chase() = 0;
};

#endif //STARFLEET_COMMAND_IBEHAVIOUR_HPP
