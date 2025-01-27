#include "Actor.h"
#include <SFML/Graphics.hpp>

Actor::Actor(Vector2f position, std::string textureFile) : texture(), sprite(texture)
{
    if (!texture.loadFromFile("../assets/texture/boat.png")) {
        throw std::runtime_error("Texture not working" + textureFile);
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Actor::draw(RenderWindow& window)
{
    window.draw(sprite);
}

void Actor::centerSpriteOrigin(Sprite &sprite)
{
    float boatWidth = sprite.getLocalBounds().size.x / 2;
    float boatHeight = sprite.getLocalBounds().size.y / 2;
    sprite.setOrigin(sprite.getLocalBounds().size / 2.0f);
}