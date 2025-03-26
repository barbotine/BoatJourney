#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Utils
{

public :
    bool static isMouseOver(RenderWindow& window, const Sprite& sprite) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    bool static isClicked(Sprite& sprite, RenderWindow& window, bool& wasPressed) {
        bool currentlyPressed = isMouseOver(window, sprite) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        if (currentlyPressed && !wasPressed) {
            wasPressed = true;
            return true;
        }
        if (!currentlyPressed) {
            wasPressed = false;
        }
        return false;
    }

    Vector2f static normalize(Vector2f vector)
    {
        float norme = sqrt(vector.x * vector.x + vector.y * vector.y);
        return Vector2f((vector.x / norme), (vector.y / norme));
    }
};




