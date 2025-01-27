#include "Actor.h"
#include <SFML/Graphics.hpp>

Actor::Actor(RenderWindow& window, Vector2f position, string actorTex) : sprite(texture), position(position)
{
    if (!texture.loadFromFile(actorTex)) {
        throw runtime_error("Texture not working");
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);
    window.draw(sprite);
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