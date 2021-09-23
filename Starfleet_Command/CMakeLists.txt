cmake_minimum_required(VERSION 3.20)
project(Starfleet_Command)

set(CMAKE_CXX_STANDARD 14)

add_executable(Starfleet_Command main.cpp Game/Game.cpp Game/Game.hpp SceneManagement/SceneManager.cpp SceneManagement/SceneManager.hpp SceneManagement/Scene.hpp SceneManagement/Scenes/MenuScene.cpp SceneManagement/Scenes/MenuScene.hpp Utility/Constants.hpp SceneManagement/Scene.cpp GameUI/Panel.cpp GameUI/Panel.hpp SceneManagement/Scenes/GameScene.cpp SceneManagement/Scenes/GameScene.hpp SceneManagement/Scenes/ShipyardScene.cpp SceneManagement/Scenes/ShipyardScene.hpp GameUI/ShipCard.cpp GameUI/ShipCard.hpp Player/PlayerStats.cpp Player/PlayerStats.hpp Player/Fleet.cpp Player/Fleet.hpp Player/Player.cpp Player/Player.hpp SpriteComponent.cpp SpriteComponent.hpp Ships/Starship.cpp Ships/Starship.hpp Ships/CommandShip.cpp Ships/CommandShip.hpp Crosshair.cpp Crosshair.hpp Utility/PredefinedColours.hpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics)
target_link_libraries(Starfleet_Command sfml-graphics)

#[[
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window audio network system REQUIRED)
target_link_libraries(Starfleet_Command PUBLIC sfml-graphics sfml-window sfml-audio sfml-network sfml-system)]]
