cmake_minimum_required(VERSION 3.19.2)
project(Starfleet_Command)

set(CMAKE_CXX_STANDARD 14)

add_executable(Starfleet_Command main.cpp Game/Game.cpp Game/Game.hpp SceneManagement/SceneManager.cpp SceneManagement/SceneManager.hpp SceneManagement/Scene.hpp SceneManagement/Scenes/MenuScene.cpp SceneManagement/Scenes/MenuScene.hpp Utility/Constants.hpp SceneManagement/Scene.cpp GameUI/Panel.cpp GameUI/Panel.hpp GameUI/ShipCard.cpp GameUI/ShipCard.hpp Player/PlayerStats.cpp Player/PlayerStats.hpp Player/Fleet.cpp Player/Fleet.hpp Components/SpriteComponent.cpp Components/SpriteComponent.hpp Ships/Starship.cpp Ships/Starship.hpp Crosshair.cpp Crosshair.hpp Utility/PredefinedColours.hpp GameUI/Button.cpp GameUI/Button.hpp ECS/GameObject.cpp ECS/GameObject.hpp ECS/Component.hpp Temporary/TestComponent.cpp Temporary/TestComponent.hpp Temporary/TestPlayer.cpp Temporary/TestPlayer.hpp Ships/Projectile.cpp Ships/Projectile.hpp SceneManagement/Scenes/GameScene.cpp SceneManagement/Scenes/GameScene.hpp Cursor.cpp Cursor.hpp Enemy.cpp Enemy.hpp Player/Player.cpp Player/Player.h Utility/Vector.cpp Utility/Vector.hpp GameUI/HealthBar.cpp GameUI/HealthBar.hpp SceneManagement/Scenes/OptionsScene.cpp SceneManagement/Scenes/OptionsScene.hpp GameUI/DamagePopUpEffect.cpp GameUI/DamagePopUpEffect.hpp GameUI/HUD.cpp GameUI/HUD.hpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics)
target_link_libraries(Starfleet_Command sfml-graphics)

#[[
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window audio network system REQUIRED)
target_link_libraries(Starfleet_Command PUBLIC sfml-graphics sfml-window sfml-audio sfml-network sfml-system)]]
