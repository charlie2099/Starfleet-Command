#include "TestClass.hpp"

void TestClass::TestFncForObserverToCall()
{
    std::cout << "OBSERVER BOI" << std::endl;
}

void TestClass::OnEvent(std::any event_data)
{
    if(auto ptr = std::any_cast<Player*>(event_data))
    {
        std::cout << ptr->GetShip()[0]->GetHealth() << std::endl;
    }

    //auto* player = reinterpret_cast<Player*>(event_data);
    //std::cout << player->GetShip()[0]->GetHealth() << std::endl;
}
