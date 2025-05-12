#ifndef STARFLEET_COMMAND_GAMESETTINGS_HPP
#define STARFLEET_COMMAND_GAMESETTINGS_HPP
#include "Utility/Colour.hpp"
#include "Utility/CustomFonts.hpp"
#include "Utility/Vector.hpp"
#include "Utility/Cursor.hpp"
#include "Sprites/UI/GUI/TextButton.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <vector>
#include <array>
#include <functional>

class GameSettings
{
public:
    enum EventID
    {
        SETTINGS_UPDATED = 0,
        SETTINGS_SAVED = 1
    };

    /*enum SettingsType { TOGGLE, COLOUR_PICKER };*/
    struct SettingsOption
    {
        sf::Text labelText;
        sf::Text valueText;
        int selectedValueIndex = 0;
        std::vector<std::string> optionValues;
        //SettingsType type;
    };

    explicit GameSettings();
    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void RepositionPanel(float xPos, float yPos);

    sf::Vector2f GetSettingsPanelSize() { return _settingsPanel.getSize(); }
    //int GetNumOfSettingOptions() { return _settingsOptions.size(); }
    SettingsOption& GetSettingOption(const std::string& settingName);
    std::vector<SettingsOption> GetSettingOptions() { return _settingsOptions; }

    void AddSettingOption(const std::string& settingName, const std::vector<std::string>& settingOptions);
    void UpdateSettingOptionValueText(const std::string& settingName, int selectedSettingsOptionValueIndex);

    using BasicEvent = std::pair<EventID, std::function<void()>>;
    void AddBasicObserver(BasicEvent observer);

private:
    void InvokeBasicEvent(EventID eventId);
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    sf::RectangleShape _settingsPanel;
    sf::Text _settingsHeaderText;
    std::vector<SettingsOption> _settingsOptions;
    std::vector<sf::Sprite> _leftArrowSprite;
    std::vector<sf::Sprite> _rightArrowSprite;
    sf::Texture _leftArrowTexture;
    sf::Texture _rightArrowTexture;
    TextButton _saveButtonPanel;
    sf::Text _settingsSavedText;
    bool _isSettingsSavedTextVisible = false;
    bool _isSaveButtonVisible = false;
    sf::SoundBuffer _buttonClickSoundBuffer;
    sf::Sound _buttonClickSound;
};

#endif //STARFLEET_COMMAND_GAMESETTINGS_HPP
