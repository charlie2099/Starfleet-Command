#include "InfoTooltip.hpp"

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
    for (int i = 0; i < _descriptionItems.size(); ++i)
    {
        window.draw(_descriptionItems[i].first);
        window.draw(_descriptionItems[i].second);
    }
}

void InfoTooltip::SetTooltipTitle(std::string title)
{
    _title.setString(title);
}

void InfoTooltip::SetTooltipItems(std::vector<std::pair<sf::Text, sf::Text>> tooltipItems)
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
        widgetInfoItem.second.setFillColor(_title.getFillColor());
        widgetInfoItem.second.setOutlineColor(sf::Color::Black);
        widgetInfoItem.second.setOutlineThickness(1.0F);

        _descriptionItems.emplace_back(widgetInfoItem);
    }
}

void InfoTooltip::SetPos(sf::Vector2<float> pos)
{
    _panel.setPosition(pos);
    _title.setPosition(_panel.getPosition().x + 5.0F, _panel.getPosition().y + 5.0F);
    /*for (int i = 0; i < _descriptionItems.size(); ++i)
    {
        _descriptionItems[i].first.setPosition(_title.getPosition().x, _title.getPosition().y + 20.0F + (i * (_descriptionItems[i].first.getGlobalBounds().height + 5.0F)));
        _descriptionItems[i].second.setPosition(_descriptionItems[i].first.getPosition().x + _descriptionItems[i].first.getGlobalBounds().width + 10.0F, _descriptionItems[i].first.getPosition().y);
    }*/
    for (int i = 0; i < _descriptionItems.size(); ++i)
    {
        if(i <= _descriptionItems.size()/2)
        {
            _descriptionItems[i].first.setPosition(_title.getPosition().x, _title.getPosition().y + 20.0F + (i * (_descriptionItems[i].first.getGlobalBounds().height + 5.0F)));
            _descriptionItems[i].second.setPosition(_descriptionItems[i].first.getPosition().x + _descriptionItems[i].first.getGlobalBounds().width + 10.0F, _descriptionItems[i].first.getPosition().y);
        }
        else
        {
            _descriptionItems[i].first.setPosition(_descriptionItems[(_descriptionItems.size()-1)/2].second.getPosition().x + _descriptionItems[(_descriptionItems.size()-1)/2].second.getGlobalBounds().width + 25.0F, _title.getPosition().y + 20.0F + ((i - (_descriptionItems.size()-1)/2) * (_descriptionItems[i].first.getGlobalBounds().height + 5.0F)));
            _descriptionItems[i].second.setPosition(_descriptionItems[i].first.getPosition().x + _descriptionItems[i].first.getGlobalBounds().width + 10.0F, _descriptionItems[i].first.getPosition().y);
        }
    }
}
