#ifndef STARFLEET_COMMAND_TESTCLASS_HPP
#define STARFLEET_COMMAND_TESTCLASS_HPP
#include <iostream>
//#include <any>
#include "Sprites/Player/Player.h"
//class Player;

class TestClass
{
public:
    void TestFncForObserverToCall();
    void OnEvent(std::any event_data);
};

#endif //STARFLEET_COMMAND_TESTCLASS_HPP
