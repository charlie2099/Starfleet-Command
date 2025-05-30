#include "GameSettings.hpp"

GameSettings::GameSettings()
{
    _settingsPanel.setSize({400.0F, 320.0F});
    _settingsPanel.setFillColor(sf::Color(0, 0, 0, 125));
    _settingsPanel.setOutlineColor(Chilli::Colour::LIGHTBLUE);
    _settingsPanel.setOutlineThickness(1.0F);

    _settingsHeaderText.setString("GAME SETTINGS");
    _settingsHeaderText.setFont(Chilli::CustomFonts::GetBoldFont());
    _settingsHeaderText.setCharacterSize(16);
    _settingsHeaderText.setFillColor(Chilli::Colour::LIGHTBLUE);
    _settingsHeaderText.setOutlineColor(sf::Color::Black);
    _settingsHeaderText.setOutlineThickness(1.0F);

    _leftArrowTexture.loadFromFile("Resources/Textures/left.png");
    _rightArrowTexture.loadFromFile("Resources/Textures/right.png");

    _saveButtonPanel.SetText("Apply settings?");
    _saveButtonPanel.SetTextSize(12);
    _saveButtonPanel.SetSize(15, 10);
    _saveButtonPanel.SetPanelColour(sf::Color(22, 155, 164, 100));

    _settingsSavedText.setString("Settings saved.\nRESTART to apply fullscreen mode.");
    _settingsSavedText.setFont(Chilli::CustomFonts::GetBoldFont());
    _settingsSavedText.setCharacterSize(10);
    _settingsSavedText.setFillColor(Chilli::Colour::TURQUOISE);
    _settingsSavedText.setOutlineColor(sf::Color::Black);
    _settingsSavedText.setOutlineThickness(1.0F);

    _buttonClickSoundBuffer.loadFromFile("Resources/Audio/click5.ogg");
    _buttonClickSound.setBuffer(_buttonClickSoundBuffer);
}

void GameSettings::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mousePos = sf::Mouse::getPosition(window);
    auto mousePosWorldCoords = window.mapPixelToCoords(mousePos);

    if(_isSaveButtonVisible)
    {
        _saveButtonPanel.EventHandler(window, event);

        if(_saveButtonPanel.IsClicked())
        {
            _buttonClickSound.play();
            InvokeBasicEvent(SETTINGS_SAVED);
            _isSettingsSavedTextVisible = true;
            _isSaveButtonVisible = false;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        for (int i = 0; i < _settingsOptions.size(); ++i)
        {
            if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, _leftArrowSprites[i].getGlobalBounds()))
            {
                _settingsOptions[i].selectedOptionIndex--;
                if(_settingsOptions[i].selectedOptionIndex <= 0)
                {
                    _settingsOptions[i].selectedOptionIndex = 0;
                }
            }
            else if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, _rightArrowSprites[i].getGlobalBounds()))
            {
                _settingsOptions[i].selectedOptionIndex++;
                if(_settingsOptions[i].selectedOptionIndex >= _settingsOptions[i].availableValues.size() - 1)
                {
                    _settingsOptions[i].selectedOptionIndex = _settingsOptions[i].availableValues.size() - 1;
                }
            }

            if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, _leftArrowSprites[i].getGlobalBounds()) or
               Chilli::Vector::BoundsCheck(mousePosWorldCoords, _rightArrowSprites[i].getGlobalBounds()))
            {
                _buttonClickSound.play();

                _isSettingsSavedTextVisible = false;
                _isSaveButtonVisible = true;

                _settingsOptions[i].currentValueText.setString(_settingsOptions[i].availableValues[_settingsOptions[i].selectedOptionIndex]);
                auto statusTextXPos = _settingsPanel.getPosition().x + _settingsPanel.getGlobalBounds().width * 0.725F - _settingsOptions[i].currentValueText.getGlobalBounds().width / 2.0F;
                _settingsOptions[i].currentValueText.setPosition({statusTextXPos, _settingsOptions[i].nameText.getPosition().y});
                InvokeBasicEvent(SETTINGS_UPDATED);
            }
        }
    }
}

void GameSettings::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mouse_pos = sf::Mouse::getPosition(window);
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos);

    for (int i = 0; i < _settingsOptions.size(); ++i)
    {
        if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, _leftArrowSprites[i].getGlobalBounds()))
        {
            //_cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
            _leftArrowSprites[i].setColor(sf::Color::Cyan);
            // isHoverOver = true?
        }
        else if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, _rightArrowSprites[i].getGlobalBounds()))
        {
            //_cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
            _rightArrowSprites[i].setColor(sf::Color::Cyan);
            // isHoverOver = true?
        }
        else
        {
            _leftArrowSprites[i].setColor(Chilli::Colour::DARKGRAY);
            _rightArrowSprites[i].setColor(Chilli::Colour::DARKGRAY);
        }
    }

    if(! _isSaveButtonVisible)
    {
        return;
    }

    _saveButtonPanel.Update(window);

    if(_saveButtonPanel.IsMouseOver())
    {
        _saveButtonPanel.SetPanelColour(sf::Color(22, 155, 164, 65));
        _saveButtonPanel.SetText(_saveButtonPanel.GetText().getString(), sf::Color::Cyan);
    }
    else if(! _saveButtonPanel.IsMouseOver())
    {
        _saveButtonPanel.SetPanelColour(sf::Color(22, 155, 164, 100));
        _saveButtonPanel.SetText(_saveButtonPanel.GetText().getString(), Chilli::Colour::LIGHTBLUE);
    }
}

void GameSettings::Render(sf::RenderWindow& window)
{
    window.draw(_settingsPanel);
    window.draw(_settingsHeaderText);
    for (int i = 0; i < _settingsOptions.size(); ++i)
    {
        window.draw(_settingsOptions[i].nameText);
        window.draw(_settingsOptions[i].currentValueText);
        window.draw(_leftArrowSprites[i]);
        window.draw(_rightArrowSprites[i]);
    }

    if(_isSaveButtonVisible)
    {
        _saveButtonPanel.Render(window);
    }

    if(_isSettingsSavedTextVisible)
    {
        window.draw(_settingsSavedText);
    }
}

void GameSettings::RepositionPanel(float xPos, float yPos)
{
    _isSettingsSavedTextVisible = false;

    _settingsPanel.setPosition({xPos, yPos});
    _settingsHeaderText.setPosition({_settingsPanel.getPosition().x + _settingsPanel.getSize().x / 2.0F - _settingsHeaderText.getGlobalBounds().width / 2.0F, _settingsPanel.getPosition().y + 20.0F});

    for (int i = 0; i < _settingsOptions.size(); ++i)
    {
        _settingsOptions[i].nameText.setPosition({_settingsPanel.getPosition().x + 25.0F, _settingsPanel.getPosition().y + 65.0F + (i * (_settingsOptions[0].nameText.getGlobalBounds().height + 20.0F))});
        auto statusTextXPos = _settingsPanel.getPosition().x + _settingsPanel.getGlobalBounds().width * 0.725F - _settingsOptions[i].currentValueText.getGlobalBounds().width / 2.0F;
        _settingsOptions[i].currentValueText.setPosition({statusTextXPos, _settingsOptions[i].nameText.getPosition().y});
        _leftArrowSprites[i].setPosition({_settingsPanel.getPosition().x + _settingsPanel.getSize().x / 2.0F, _settingsOptions[i].currentValueText.getPosition().y + 1.0F});
        _rightArrowSprites[i].setPosition({statusTextXPos + _settingsPanel.getGlobalBounds().width * 0.225F + _settingsOptions[i].currentValueText.getGlobalBounds().width / 2.0F - 10.0F, _settingsOptions[i].currentValueText.getPosition().y + 1.0F});
    }

    //_saveButtonPanel.SetPosition(_settingsPanel.getPosition().x + _settingsPanel.getSize().x/2.0F - _saveButtonPanel.GetTextSize().width/2.0F, _settingsPanel.getPosition().y + _settingsPanel.getSize().y - _saveButtonPanel.GetPanelSize().height - 7.5F);
    _saveButtonPanel.SetPosition(_settingsOptions[0].nameText.getPosition().x + 12.5F, _settingsPanel.getPosition().y + _settingsPanel.getSize().y - _saveButtonPanel.GetPanelSize().height - 10.0F);

    //_settingsSavedText.setPosition(_settingsPanel.getPosition().x + _settingsPanel.getSize().x - _settingsSavedText.getGlobalBounds().width - 20.0F, _saveButtonPanel.GetTextPosition().y + _saveButtonPanel.GetTextSize().height/4.0F);
    //_settingsSavedText.setPosition(_settingsPanel.getPosition().x + _settingsPanel.getSize().x - _settingsSavedText.getGlobalBounds().width - 15.0F, _saveButtonPanel.GetPanelPosition().y + 1.0F);
    _settingsSavedText.setPosition(_saveButtonPanel.GetPanelPosition().x, _saveButtonPanel.GetPanelPosition().y + 1.0F);
}

void GameSettings::AddSettingOption(const std::string &settingName, const std::vector<std::string>& settingOptions)
{
    SettingsOption newSetting;
    newSetting.nameText.setString(settingName);
    //newSetting.type = SettingsType::TOGGLE;
    //newSetting.selectedOptionIndex = 1;
    for (auto & settingElement : settingOptions)
    {
        newSetting.availableValues.emplace_back(settingElement);
    }
    newSetting.nameText.setFont(Chilli::CustomFonts::GetBoldFont());
    newSetting.nameText.setCharacterSize(12);
    newSetting.nameText.setFillColor(sf::Color::White);
    newSetting.nameText.setOutlineColor(sf::Color::Black);
    newSetting.nameText.setOutlineThickness(1.0F);
    newSetting.currentValueText.setString(newSetting.availableValues[newSetting.selectedOptionIndex]);
    newSetting.currentValueText.setFont(Chilli::CustomFonts::GetBoldFont());
    newSetting.currentValueText.setCharacterSize(12);
    newSetting.currentValueText.setFillColor(sf::Color::White);
    newSetting.currentValueText.setOutlineColor(sf::Color::Black);
    newSetting.currentValueText.setOutlineThickness(1.0F);
    _settingsOptions.emplace_back(newSetting);

    sf::Sprite newLeftArrowSprite;
   newLeftArrowSprite.setTexture(_leftArrowTexture);
   newLeftArrowSprite.scale(0.25F, 0.25F);
   newLeftArrowSprite.setColor(Chilli::Colour::LIGHTBLUE);
   _leftArrowSprites.emplace_back(newLeftArrowSprite);

    sf::Sprite newRightArrowSprite;
    newRightArrowSprite.setTexture(_rightArrowTexture);
    newRightArrowSprite.scale(0.25F, 0.25F);
    newRightArrowSprite.setColor(Chilli::Colour::LIGHTBLUE);
    _rightArrowSprites.emplace_back(newRightArrowSprite);
}

void GameSettings::SetSettingOptionValueText(const std::string &settingName, int selectedSettingsOptionValueIndex)
{
    // TODO: Create and utilise a dictionary instead?
    for (auto & _settingsOption : _settingsOptions)
    {
        if(_settingsOption.nameText.getString() == settingName)
        {
            _settingsOption.selectedOptionIndex = selectedSettingsOptionValueIndex;
            _settingsOption.currentValueText.setString(_settingsOption.availableValues[_settingsOption.selectedOptionIndex]);
        }
    }
}

void GameSettings::SetSettingOptionValueColour(const std::string& settingName, sf::Color colour)
{
    GetSettingOption(settingName).currentValueText.setFillColor(colour);
}

GameSettings::SettingsOption &GameSettings::GetSettingOption(const std::string &settingName)
{
    // TODO: Use std::map instead?
    for (auto& option : _settingsOptions)
    {
        if (option.nameText.getString() == settingName)
        {
            return option;
        }
    }
    throw std::runtime_error("Setting option '" + settingName + "' not found");
}

void GameSettings::AddBasicObserver(GameSettings::BasicEvent observer)
{
    _basicObservers.insert(observer);
}

void GameSettings::InvokeBasicEvent(GameSettings::EventID eventId)
{
    /// Invokes the callback function assigned to the specified event id?
    auto range = _basicObservers.equal_range(eventId);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        iter->second();
    }
}
