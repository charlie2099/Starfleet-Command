cmake_minimum_required(VERSION 3.20)
project(Starfleet_Command)

set(CMAKE_CXX_STANDARD 14)

add_executable(Starfleet_Command main.cpp Game/Game.cpp Game/Game.hpp SceneManagement/SceneManager.cpp SceneManagement/SceneManager.hpp SceneManagement/Scene.hpp SceneManagement/Scenes/MenuScene.cpp SceneManagement/Scenes/MenuScene.hpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics)
target_link_libraries(Starfleet_Command sfml-graphics)

#[[
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window audio network system REQUIRED)
target_link_libraries(Starfleet_Command PUBLIC sfml-graphics sfml-window sfml-audio sfml-network sfml-system)]]
