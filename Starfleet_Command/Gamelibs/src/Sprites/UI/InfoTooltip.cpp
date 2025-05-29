#include "Sprites/UI/InfoTooltip.hpp"

InfoTooltip::InfoTooltip(sf::Vector2<float> widgetPanelSize, sf::Color _widgetPanelColour, const std::string& widgetTitle, std::vector<std::pair<sf::Text, sf::Text>> widgetInfoItems)
{
    _panel.setSize(widgetPanelSize);
    _panel.setFillColor({_widgetPanelColour.r, _widgetPanelColour.g, _widgetPanelColour.b, 50});
    _panel.setOutlineColor(_widgetPanelColour);
    _panel.setOutlineThickness(1.0F);
    _panel.setPosition(200.0F, 200.0F);

    _title.setString(widgetTitle);
    _title.setFont(Chilli::CustomFonts::GetBoldFont());
    _title.setCharacterSize(10.0F);
    _title.setFillColor(_widgetPanelColour);
    _title.setOutlineColor(sf::Color::Black);
    _title.setOutlineThickness(1.0F);
    _title.setPosition(_panel.getPosition().x + 10.0F, _panel.getPosition().y + 10.0F);

    _description.setString("Some description");
    _description.setFont(Chilli::CustomFonts::GetBoldFont());
    _description.setCharacterSize(8.0F);
    _description.setFillColor(_widgetPanelColour);
    _description.setOutlineColor(sf::Color::Black);
    _description.setOutlineThickness(1.0F);
    _description.setPosition(_title.getPosition().x, _title.getPosition().y + 20.0F);

    for (auto & widgetInfoItem : widgetInfoItems)
    {
        widgetInfoItem.first.setFont(Chilli::CustomFonts::GetBoldFont());
        widgetInfoItem.first.setCharacterSize(8.0F);
        widgetInfoItem.first.setFillColor(_widgetPanelColour);
        widgetInfoItem.first.setOutlineColor(sf::Color::Black);
        widgetInfoItem.first.setOutlineThickness(1.0F);

        widgetInfoItem.second.setFont(Chilli::CustomFonts::GetBoldFont());
        widgetInfoItem.second.setCharacterSize(8.0F);
        widgetInfoItem.second.setFillColor(_widgetPanelColour);
        widgetInfoItem.second.setOutlineColor(sf::Color::Black);
        widgetInfoItem.second.setOutlineThickness(1.0F);

        _descriptionItems.emplace_back(widgetInfoItem);
    }
}

void InfoTooltip::EventHandler(sf::RenderWindow &window, sf::Event &event)
{

}

void InfoTooltip::Update(sf::RenderWindow &window, sf::Time deltaTime)
{

}

void InfoTooltip::Render(sf::RenderWindow &window)
{
    window.draw(_panel);
    window.draw(_title);
    window.draw(_description);
    for (int i = 0; i < _descriptionItems.size(); ++i)
    {
        window.draw(_descriptionItems[i].first);
        window.draw(_descriptionItems[i].second);
    }
}

void InfoTooltip::SetTitle(const std::string& title)
{
    _title.setString(title);
}

void InfoTooltip::SetDescription(const std::string& description)
{
    _description.setString(description);
}

void InfoTooltip::SetItems(std::vector<std::pair<sf::Text, sf::Text>> tooltipItems)
{
    _descriptionItems.clear();

    for (auto & widgetInfoItem : tooltipItems)
    {
        widgetInfoItem.first.setFont(Chilli::CustomFonts::GetBoldFont());
        widgetInfoItem.first.setCharacterSize(8.0F);
        widgetInfoItem.first.setFillColor(_title.getFillColor());
        widgetInfoItem.first.setOutlineColor(sf::Color::Black);
        widgetInfoItem.first.setOutlineThickness(1.0F);

        widgetInfoItem.second.setFont(Chilli::CustomFonts::GetBoldFont());
        widgetInfoItem.second.setCharacterSize(8.0F);
        widgetInfoItem.second.setFillColor(sf::Color::White);
        widgetInfoItem.second.setOutlineColor(sf::Color::Black);
        widgetInfoItem.second.setOutlineThickness(1.0F);

        _descriptionItems.emplace_back(widgetInfoItem);
    }
}

void InfoTooltip::SetPos(sf::Vector2<float> pos)
{
    _panel.setPosition(pos);
    _title.setPosition(_panel.getPosition().x + 5.0F, _panel.getPosition().y + 5.0F);
    _description.setPosition(_title.getPosition().x, _title.getPosition().y + 20.0F);

    if(_descriptionItems.empty())
    {
        return;
    }

    int longestTextWidthCol1 = 0;
    for (int i = 0; i < _descriptionItems.size()/2; ++i)
    {
        longestTextWidthCol1 = std::max(longestTextWidthCol1, static_cast<int>(_descriptionItems[i].first.getGlobalBounds().width));
    }

    int longestTextWidthCol2 = 0;
    for (int i = _descriptionItems.size()/2; i < _descriptionItems.size(); ++i)
    {
        longestTextWidthCol2 = std::max(longestTextWidthCol2, static_cast<int>(_descriptionItems[i].first.getGlobalBounds().width));
    }

    const float SPACING_X_OFFSET = 5.0F;
    const float SPACING_Y_OFFSET = 5.0F;
    for (int i = 0; i < _descriptionItems.size(); ++i)
    {
        if(i < _descriptionItems.size()/2)
        {
            _descriptionItems[i].first.setPosition(_description.getPosition().x, _description.getPosition().y + _description.getGlobalBounds().height + SPACING_Y_OFFSET + (i * (_descriptionItems[i].first.getGlobalBounds().height + 5.0F)));
            _descriptionItems[i].second.setPosition(_descriptionItems[i].first.getPosition().x + longestTextWidthCol1 + SPACING_X_OFFSET, _descriptionItems[i].first.getPosition().y);
        }
        else
        {
            _descriptionItems[i].first.setPosition(_descriptionItems[(_descriptionItems.size()-1)/2].second.getPosition().x + _descriptionItems[(_descriptionItems.size()-1)/2].second.getGlobalBounds().width + 25.0F, _description.getPosition().y + _description.getGlobalBounds().height + SPACING_Y_OFFSET + (i - (_descriptionItems.size())/2) * (_descriptionItems[i].first.getGlobalBounds().height + 5.0F));
            _descriptionItems[i].second.setPosition(_descriptionItems[i].first.getPosition().x + longestTextWidthCol2 + SPACING_X_OFFSET, _descriptionItems[i].first.getPosition().y);
        }
    }
}
