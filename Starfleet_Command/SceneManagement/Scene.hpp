#ifndef STARFLEET_COMMAND_SCENE_HPP
#define STARFLEET_COMMAND_SCENE_HPP
#include <SFML/Graphics.hpp>

class Scene
        {
        public:
            explicit Scene() = default;
            virtual ~Scene() = default;

            enum class ID
                    {
                MENU = 0,
                OPTIONS,
                MODE_SELECT,
                HOWTOPLAY,
                SINGLEPLAYER,
                SPLIT_SCREEN,
                LEVEL_EDITIOR,
                WIN,
                LOSE
                    };

            // Pure virtual functions
            virtual bool init()                                                     = 0;
            virtual void eventHandler(sf::RenderWindow& window, sf::Event& event)   = 0;
            virtual void update(sf::RenderWindow &window, sf::Time deltaTime)       = 0;
            virtual void render(sf::RenderWindow& window)                           = 0;

            void setScene(Scene::ID scene) { scene_id = scene; }
            [[nodiscard]] ID getScene() const { return scene_id; }

        private:
            ID scene_id{};
        };

#endif //STARFLEET_COMMAND_SCENE_HPP
