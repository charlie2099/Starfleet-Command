cmake_minimum_required(VERSION 3.19.2)
project(Starfleet_Command)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(Starfleet_Command main.cpp Game/Game.cpp Game/Game.hpp Gamelibs/src/Scenes/SceneManager.cpp Gamelibs/include/Scenes/SceneManager.hpp Gamelibs/include/Scenes/Scene.hpp Gamelibs/src/Scenes/MenuScene.cpp Gamelibs/include/Scenes/MenuScene.hpp Gamelibs/include/Utility/Constants.hpp Gamelibs/src/Sprites/UI/Panel.cpp Gamelibs/include/Sprites/UI/Panel.hpp Gamelibs/src/Components/SpriteComponent.cpp Gamelibs/include/Components/SpriteComponent.hpp Gamelibs/include/Utility/PredefinedColours.hpp Gamelibs/src/Sprites/UI/GUI/Button.cpp Gamelibs/include/Sprites/UI/GUI/Button.hpp Gamelibs/src/Sprites/Projectiles/Projectile.cpp Gamelibs/include/Sprites/Projectiles/Projectile.hpp Gamelibs/src/Scenes/GameScene.cpp Gamelibs/include/Scenes/GameScene.hpp Gamelibs/src/Utility/Cursor.cpp Gamelibs/include/Utility/Cursor.hpp Gamelibs/src/Sprites/Enemy/Enemy.cpp Gamelibs/include/Sprites/Enemy/Enemy.hpp Gamelibs/src/Sprites/Player/Player.cpp Gamelibs/include/Sprites/Player/Player.hpp Gamelibs/src/Utility/Vector.cpp Gamelibs/include/Utility/Vector.hpp Gamelibs/src/Sprites/UI/HealthBar.cpp Gamelibs/include/Sprites/UI/HealthBar.hpp Gamelibs/src/Scenes/SplashScene.cpp Gamelibs/include/Scenes/SplashScene.hpp Gamelibs/src/Sprites/UI/Effects/PopupText.cpp Gamelibs/include/Sprites/UI/Effects/PopupText.hpp Gamelibs/include/Interfaces/IStarship.hpp Gamelibs/src/Sprites/Starships/StarshipFactory.cpp Gamelibs/include/Sprites/Starships/StarshipFactory.hpp Gamelibs/src/Sprites/Starships/StarshipClasses/LightFighter.cpp Gamelibs/include/Sprites/Starships/StarshipClasses/LightFighter.hpp Gamelibs/src/Components/HealthComponent.cpp Gamelibs/include/Components/HealthComponent.hpp Gamelibs/include/Sprites/Starships/StarshipClasses/HeavyFighter.hpp Gamelibs/src/Sprites/Starships/StarshipClasses/HeavyFighter.cpp Gamelibs/include/Sprites/Starships/StarshipClasses/SupportFrigate.hpp Gamelibs/include/Sprites/Starships/StarshipClasses/Dreadnought.hpp Gamelibs/include/Sprites/Starships/StarshipClasses/Mothership.hpp Gamelibs/include/Sprites/Starships/StarshipClasses/Battleship.hpp Gamelibs/src/Sprites/Starships/StarshipClasses/SupportFrigate.cpp Gamelibs/src/Sprites/Starships/StarshipClasses/Dreadnought.cpp Gamelibs/src/Sprites/Starships/StarshipClasses/Battleship.cpp Gamelibs/src/Sprites/Starships/StarshipClasses/Mothership.cpp
        Gamelibs/src/SpaceLane.cpp
        Gamelibs/include/SpaceLane.hpp
        Gamelibs/src/Sprites/UI/ProgressBar.cpp
        Gamelibs/include/Sprites/UI/ProgressBar.hpp
        Gamelibs/src/Minimap.cpp
        Gamelibs/include/Minimap.hpp
        Gamelibs/src/ScrapMetalManager.cpp
        Gamelibs/include/ScrapMetalManager.hpp
        Gamelibs/src/ParallaxBackground.cpp
        Gamelibs/include/ParallaxBackground.hpp
        Gamelibs/src/MothershipStatusDisplay.cpp
        Gamelibs/include/MothershipStatusDisplay.hpp
        Gamelibs/src/Utility/CustomFonts.cpp
        Gamelibs/include/Utility/CustomFonts.hpp
        Gamelibs/src/StarshipDeploymentButton.cpp
        Gamelibs/include/StarshipDeploymentButton.hpp
        Gamelibs/src/StarshipDeploymentManager.cpp
        Gamelibs/include/StarshipDeploymentManager.hpp
        Gamelibs/src/Utility/RNG.cpp
        Gamelibs/include/Utility/RNG.hpp
        Gamelibs/src/AIDirector/AiDirector.cpp
        Gamelibs/include/AIDirector/AiDirector.hpp
        Gamelibs/src/AIDirector/RuleCalculator/DirectorIntensityRulesCalculator.cpp
        Gamelibs/include/AIDirector/RuleCalculator/DirectorIntensityRulesCalculator.hpp
        Gamelibs/include/AIDirector/Rules/IntensityRules/IDirectorIntensityRule.hpp
        Gamelibs/src/AIDirector/RuleEngine/DirectorIntensityRuleEngine.cpp
        Gamelibs/include/AIDirector/RuleEngine/DirectorIntensityRuleEngine.hpp
        Gamelibs/src/AIDirector/Rules/IntensityRules/EnemyMothershipHealthLow_IntensityRule.cpp
        Gamelibs/include/AIDirector/Rules/IntensityRules/EnemyMothershipHealthLow_IntensityRule.hpp
        Gamelibs/include/AIDirector/DirectorEventBus.hpp
        Gamelibs/src/AIDirector/DirectorEventBus.cpp
        Gamelibs/src/Utility/StateMachine.cpp
        Gamelibs/include/Utility/StateMachine.hpp
        Gamelibs/src/AIDirector/States/DirectorRespiteState.cpp
        Gamelibs/include/AIDirector/States/DirectorRespiteState.hpp
        Gamelibs/src/AIDirector/States/DirectorBuildUpState.cpp
        Gamelibs/include/AIDirector/States/DirectorBuildUpState.hpp
        Gamelibs/src/AIDirector/States/DirectorPeakState.cpp
        Gamelibs/include/AIDirector/States/DirectorPeakState.hpp
        Gamelibs/src/AIDirector/States/DirectorPeakFadeState.cpp
        Gamelibs/include/AIDirector/States/DirectorPeakFadeState.hpp
        Gamelibs/include/AIDirector/Rules/IntensityRules/PlayerMothershipHealthLow_IntensityRule.hpp
        Gamelibs/src/AIDirector/Rules/IntensityRules/PlayerMothershipHealthLow_IntensityRule.cpp
        Gamelibs/include/AIDirector/Rules/BehaviourRules/IDirectorBehaviourRule.hpp
        Gamelibs/src/AIDirector/RuleCalculator/DirectorBehaviourRulesEvaluator.cpp
        Gamelibs/include/AIDirector/RuleCalculator/DirectorBehaviourRulesEvaluator.hpp
        Gamelibs/src/AIDirector/RuleEngine/DirectorBehaviourRuleEngine.cpp
        Gamelibs/include/AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp
        Gamelibs/src/AIDirector/Rules/BehaviourRules/SpawnWeakStarshipsAtStart_BehaviourRule.cpp
        Gamelibs/include/AIDirector/Rules/BehaviourRules/SpawnWeakStarshipsAtStart_BehaviourRule.hpp
        Gamelibs/src/AIDirector/Rules/IntensityRules/EnemyStarshipsInPlay_IntensityRule.cpp
        Gamelibs/include/AIDirector/Rules/IntensityRules/EnemyStarshipsInPlay_IntensityRule.hpp
        Gamelibs/src/AIDirector/Rules/IntensityRules/PlayerStarshipsInPlay_IntensityRule.cpp
        Gamelibs/include/AIDirector/Rules/IntensityRules/PlayerStarshipsInPlay_IntensityRule.hpp
        Gamelibs/src/AIDirector/Rules/IntensityRules/PlayerScrapSurplus_IntensityRule.cpp
        Gamelibs/include/AIDirector/Rules/IntensityRules/PlayerScrapSurplus_IntensityRule.hpp
        Gamelibs/src/AIDirector/Rules/BehaviourRules/CounterAttack_BehaviourRule.cpp
        Gamelibs/include/AIDirector/Rules/BehaviourRules/CounterAttack_BehaviourRule.hpp
        Gamelibs/src/AIDirector/Rules/BehaviourRules/PlayerSpacelaneDominance_BehaviourRule.cpp
        Gamelibs/include/AIDirector/Rules/BehaviourRules/PlayerSpacelaneDominance_BehaviourRule.hpp
        Gamelibs/include/Scenes/VictoryScene.hpp
        Gamelibs/include/Scenes/DefeatScene.hpp
        Gamelibs/src/Scenes/VictoryScene.cpp
        Gamelibs/src/Scenes/DefeatScene.cpp
        Gamelibs/UpgradeScrapCollectionButton.cpp
        Gamelibs/UpgradeScrapCollectionButton.hpp
        Gamelibs/src/Utility/JsonSaveSystem.cpp
        Gamelibs/include/Utility/JsonSaveSystem.hpp
        Gamelibs/GameSettings.cpp
        Gamelibs/GameSettings.hpp
)

include_directories(Gamelibs/include)
include_directories(Gamelibs/src)
include_directories(ExternalPackages)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window audio network system REQUIRED)
target_link_libraries(Starfleet_Command PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

#[[
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window audio network system REQUIRED)
target_link_libraries(Starfleet_Command PUBLIC sfml-graphics sfml-window sfml-audio sfml-network sfml-system)]]
