#include "Scenes/Scene.hpp"

Scene::Scene()
{
    LoadFont();
}

bool Scene::LoadFont()
{
    if(!game_font_r.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }
    if(!game_font_b.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Bold.ttf"))
    {
        return false;
    }
    return true;
}





