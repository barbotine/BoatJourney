#include "Resource.h"

Resource::Resource(Vector2f spritePosition,Texture& texture, Vector2f textPosition, int value) : resourceValue(font), sprite(texture)
{
    sprite.setTexture(texture);
    sprite.setPosition(spritePosition);

    if (!font.openFromFile("../assets/font/Roboto-Italic.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police\n";
    }

    resourceValue.setFont(font);
    resourceValue.setString(to_string(value));
    resourceValue.setCharacterSize(24);
    resourceValue.setFillColor(sf::Color::White);
    resourceValue.setPosition(textPosition);
}

void Resource::update(RenderWindow& window, int value)
{

}

void Resource::setText(int value) {
    resourceValue.setString(to_string(value));
}

void Resource::draw(sf::RenderWindow& window)
{
    window.draw(resourceValue);
    window.draw(sprite);
}

