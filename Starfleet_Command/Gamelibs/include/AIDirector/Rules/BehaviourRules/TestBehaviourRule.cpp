#include "TestBehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

TestBehaviourRule::TestBehaviourRule()
{

}

void TestBehaviourRule::ApplyBehaviour(AiDirector &director)
{
    // TODO: Create a timer that resets every time the condition below is called? Then the director.SpawnEnemy method will be called every x amount of time whilst the condition is still met?
    if(director.GetEnemyMothershipHealth() == 10000)
    {
        director.SpawnEnemy(StarshipFactory::DESTROYER, 2);
    }
}
