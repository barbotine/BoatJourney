#include "Button.h"

Button::Button(float x, float y, float width, float height, const sf::Color& color, const std::string& textString) : text(font) {
    shape.setPosition(Vector2f(x, y));
    shape.setSize({ width, height });
    shape.setFillColor(color);

    if (!font.openFromFile("../assets/font/Roboto-Italic.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police\n";
    }

    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(Vector2f(
        x + (width - text.getLocalBounds().size.x) / 2,
        y + (height - text.getLocalBounds().size.y) / 2)
    );
}

bool Button::isClicked(sf::RenderWindow& window) {
    bool currentlyPressed = isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (currentlyPressed && !wasPressed) {
        wasPressed = true;
        return true;
    }
    if (!currentlyPressed) {
        wasPressed = false;
    }
    return false;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return shape.getGlobalBounds().contains(Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
}


void Button::setOutlineColor(Color color) {
    shape.setOutlineColor(color);
}

void Button::setOutlineThickness(float thickness) {
    shape.setOutlineThickness(thickness);
}