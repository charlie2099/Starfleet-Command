#include "Scene.hpp"

Scene::Scene()
{
    LoadFont();
}

bool Scene::LoadFont()
{
    if(!game_font_r.loadFromFile("fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }
    if(!game_font_b.loadFromFile("fonts/Orbitron/Orbitron-Bold.ttf"))
    {
        return false;
    }
    return true;
}





