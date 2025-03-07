#include "Resource.h"

Resource::Resource(Vector2f position,Texture& texture) : Actor(position, texture), resourceValue(font)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);

    if (!font.openFromFile("../assets/font/Roboto-Italic.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police\n";
    }

    resourceValue.setFont(font);
    resourceValue.setString(to_string(3));
    resourceValue.setCharacterSize(24);
    resourceValue.setFillColor(sf::Color::White);
    resourceValue.setPosition(Vector2f(1700, 800));
}

void Resource::update(RenderWindow& window)
{

}

void Resource::createText(int value)
{
    resourceValue.setFont(font);
    resourceValue.setString(to_string(value));
    resourceValue.setCharacterSize(24);
    resourceValue.setFillColor(sf::Color::White);
    resourceValue.setPosition(Vector2f(1750, 800));
        
}

void Resource::draw(sf::RenderWindow& window)
{
    window.draw(resourceValue);
    window.draw(sprite);
}
