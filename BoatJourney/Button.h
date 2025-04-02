#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Button {
public:
    bool isClicked(sf::RenderWindow& window);
    Button(float x, float y, float width, float height, const sf::Color& color, const std::string& textString);
    void draw(sf::RenderWindow& window);
    bool isMouseOver(sf::RenderWindow& window);

    void setOutlineColor(Color color);

    void setOutlineThickness(float thickness);

private:
    RectangleShape shape;
    Font font;
    Text text;
    bool wasPressed = false;
};



