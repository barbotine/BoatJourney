#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class ProgressBar {
public:
    ProgressBar(float positionX, float positionY);

    void update(float value, float maxValue);
    void draw(RenderWindow& window);

protected:
    RectangleShape backgroundBar;
    RectangleShape fillBar;
    float maxWidth;
    float width;
    float height;
    sf::Color fillColor;
    sf::Color backgroundColor;

};

