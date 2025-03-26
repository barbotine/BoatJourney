#include "ProgressBar.h"


ProgressBar::ProgressBar(float positionX, float positionY) : width(200), height(20), // Valeurs par défaut
fillColor(sf::Color::Green), backgroundColor(sf::Color(50, 50, 50))
{
    maxWidth = width;

    backgroundBar.setSize(sf::Vector2f(width, height));
    backgroundBar.setPosition(sf::Vector2f(positionX, positionY));
    backgroundBar.setFillColor(backgroundColor);

    fillBar.setSize(sf::Vector2f(width, height));
    fillBar.setPosition(sf::Vector2f(positionX, positionY));
    fillBar.setFillColor(fillColor);
}

void ProgressBar::update(float value, float maxValue)
{
    float percentage = value / maxValue;
    fillBar.setSize(sf::Vector2f(maxWidth * percentage, fillBar.getSize().y));
}

void ProgressBar::draw(RenderWindow& window)
{
    window.draw(backgroundBar);
    window.draw(fillBar);
}
