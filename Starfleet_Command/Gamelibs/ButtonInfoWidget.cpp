#include "ButtonInfoWidget.hpp"

ButtonInfoWidget::ButtonInfoWidget(sf::Vector2<float> widgetPanelSize, sf::Color _widgetPanelColour, const std::string& widgetTitle, std::vector<std::pair<sf::Text, sf::Text>> widgetInfoItems)
{
    _widgetPanel.setSize(widgetPanelSize);
    _widgetPanel.setFillColor({_widgetPanelColour.r, _widgetPanelColour.g, _widgetPanelColour.b, 50});
    _widgetPanel.setOutlineColor(Chilli::Colour::LIGHTBLUE);
    _widgetPanel.setOutlineThickness(1.0F);
    _widgetPanel.setPosition(200.0F, 200.0F);

    _widgetTitle.setString(widgetTitle);
    _widgetTitle.setFont(Chilli::CustomFonts::GetBoldFont());
    _widgetTitle.setCharacterSize(10.0F);
    _widgetTitle.setFillColor(_widgetPanelColour);
    _widgetTitle.setOutlineColor(sf::Color::Black);
    _widgetTitle.setOutlineThickness(1.0F);
    _widgetTitle.setPosition(_widgetPanel.getPosition().x + 10.0F, _widgetPanel.getPosition().y + 10.0F);

    for (auto & widgetInfoItem : widgetInfoItems)
    {
        widgetInfoItem.first.setFont(Chilli::CustomFonts::GetBoldFont());
        widgetInfoItem.first.setCharacterSize(8.0F);
        widgetInfoItem.first.setFillColor(Chilli::Colour::LIGHTBLUE);
        widgetInfoItem.first.setOutlineColor(sf::Color::Black);
        widgetInfoItem.first.setOutlineThickness(1.0F);

        widgetInfoItem.second.setFont(Chilli::CustomFonts::GetBoldFont());
        widgetInfoItem.second.setCharacterSize(8.0F);
        widgetInfoItem.second.setFillColor(Chilli::Colour::LIGHTBLUE);
        widgetInfoItem.second.setOutlineColor(sf::Color::Black);
        widgetInfoItem.second.setOutlineThickness(1.0F);

        _widgetTextValueItems.emplace_back(widgetInfoItem);
    }
}

void ButtonInfoWidget::EventHandler(sf::RenderWindow &window, sf::Event &event)
{

}

void ButtonInfoWidget::Update(sf::RenderWindow &window, sf::Time deltaTime)
{

}

void ButtonInfoWidget::Render(sf::RenderWindow &window)
{
    window.draw(_widgetPanel);
    window.draw(_widgetTitle);
    for (int i = 0; i < _widgetTextValueItems.size(); ++i)
    {
        window.draw(_widgetTextValueItems[i].first);
        window.draw(_widgetTextValueItems[i].second);
    }
}

void ButtonInfoWidget::SetPos(sf::Vector2<float> pos)
{
    _widgetPanel.setPosition(pos);
    _widgetTitle.setPosition(_widgetPanel.getPosition().x + 5.0F, _widgetPanel.getPosition().y + 5.0F);
    for (int i = 0; i < _widgetTextValueItems.size(); ++i)
    {
        _widgetTextValueItems[i].first.setPosition(_widgetTitle.getPosition().x, _widgetTitle.getPosition().y + 20.0F + (i * (_widgetTextValueItems[i].first.getGlobalBounds().height + 5.0F)));
        _widgetTextValueItems[i].second.setPosition(_widgetTextValueItems[i].first.getPosition().x + _widgetTextValueItems[i].first.getGlobalBounds().width + 10.0F, _widgetTextValueItems[i].first.getPosition().y);
    }
}
