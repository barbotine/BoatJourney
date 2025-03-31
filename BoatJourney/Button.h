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

    private:
        sf::RectangleShape shape;
        sf::Font font;
        sf::Text text;
        bool wasPressed = false;
};



