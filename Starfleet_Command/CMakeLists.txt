cmake_minimum_required(VERSION 3.19.2)
project(Starfleet_Command)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(Starfleet_Command main.cpp Game/Game.cpp Game/Game.hpp Gamelibs/src/Scenes/SceneManager.cpp Gamelibs/include/Scenes/SceneManager.hpp Gamelibs/include/Scenes/Scene.hpp Gamelibs/src/Scenes/MenuScene.cpp Gamelibs/include/Scenes/MenuScene.hpp Gamelibs/include/Utility/Constants.hpp Gamelibs/src/Scenes/Scene.cpp Gamelibs/src/Sprites/UI/HUD/Panel.cpp Gamelibs/include/Sprites/UI/HUD/Panel.hpp Gamelibs/src/Sprites/Player/PlayerStats.cpp Gamelibs/include/Sprites/Player/PlayerStats.hpp Gamelibs/src/Components/SpriteComponent.cpp Gamelibs/include/Components/SpriteComponent.hpp Gamelibs/include/Utility/PredefinedColours.hpp Gamelibs/src/Sprites/UI/GUI/Button.cpp Gamelibs/include/Sprites/UI/GUI/Button.hpp Gamelibs/src/Sprites/Projectiles/Projectile.cpp Gamelibs/include/Sprites/Projectiles/Projectile.hpp Gamelibs/src/Scenes/GameScene.cpp Gamelibs/include/Scenes/GameScene.hpp Gamelibs/src/Utility/Cursor.cpp Gamelibs/include/Utility/Cursor.hpp Gamelibs/src/Sprites/Enemy/Enemy.cpp Gamelibs/include/Sprites/Enemy/Enemy.hpp Gamelibs/src/Sprites/Player/Player.cpp Gamelibs/include/Sprites/Player/Player.h Gamelibs/src/Utility/Vector.cpp Gamelibs/include/Utility/Vector.hpp Gamelibs/src/Sprites/UI/HUD/HealthBar.cpp Gamelibs/include/Sprites/UI/HUD/HealthBar.hpp Gamelibs/src/Scenes/OptionsScene.cpp Gamelibs/include/Scenes/OptionsScene.hpp Gamelibs/src/Sprites/UI/Effects/DamagePopUpEffect.cpp Gamelibs/include/Sprites/UI/Effects/DamagePopUpEffect.hpp Gamelibs/include/Interfaces/IStarship.hpp Gamelibs/src/Sprites/Starships/StarshipFactory.cpp Gamelibs/include/Sprites/Starships/StarshipFactory.hpp Gamelibs/src/Sprites/Starships/StarshipClasses/LightFighter.cpp Gamelibs/include/Sprites/Starships/StarshipClasses/LightFighter.hpp Gamelibs/src/Components/HealthComponent.cpp Gamelibs/include/Components/HealthComponent.hpp Gamelibs/include/Sprites/Starships/StarshipClasses/HeavyFighter.hpp Gamelibs/src/Sprites/Starships/StarshipClasses/HeavyFighter.cpp Gamelibs/include/Sprites/Starships/StarshipClasses/SupportShip.hpp Gamelibs/include/Sprites/Starships/StarshipClasses/Destroyer.hpp Gamelibs/include/Sprites/Starships/StarshipClasses/Mothership.hpp Gamelibs/include/Sprites/Starships/StarshipClasses/Battleship.hpp Gamelibs/src/Sprites/Starships/StarshipClasses/SupportShip.cpp Gamelibs/src/Sprites/Starships/StarshipClasses/Destroyer.cpp Gamelibs/src/Sprites/Starships/StarshipClasses/Battleship.cpp Gamelibs/src/Sprites/Starships/StarshipClasses/Mothership.cpp
        Gamelibs/src/Sprites/SpaceLane.cpp
        Gamelibs/include/Sprites/SpaceLane.hpp
        Gamelibs/src/Sprites/UI/HUD/ProgressBar.cpp
        Gamelibs/include/Sprites/UI/HUD/ProgressBar.hpp
        Gamelibs/UIElement.hpp
        Gamelibs/TextElement.cpp
        Gamelibs/TextElement.hpp
        Gamelibs/ImageElement.cpp
        Gamelibs/ImageElement.hpp
        Gamelibs/InfoBoxElement.cpp
        Gamelibs/InfoBoxElement.hpp
        Gamelibs/ButtonElement.cpp
        Gamelibs/ButtonElement.hpp
        Gamelibs/TextButtonElement.cpp
        Gamelibs/TextButtonElement.hpp
)

include_directories(Gamelibs/include)
include_directories(Gamelibs/src)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics)
target_link_libraries(Starfleet_Command sfml-graphics)

#[[
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window audio network system REQUIRED)
target_link_libraries(Starfleet_Command PUBLIC sfml-graphics sfml-window sfml-audio sfml-network sfml-system)]]
