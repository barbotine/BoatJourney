#include "Character.h"

Character::Character(Vector2f position, Texture& texture) : Actor(position, texture)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    this->solarResource = 0;
    this->life = 10;
    this->food = 10;
    this->water = 10;
}

void Character::makingSolarEnergy(Sun &sun, RenderWindow& window)
{
    if (sun.getIsVisible() && isMaxResourceNotReach(solarResource))
    {
        cout << "Adding solar resource" << endl;
        ++solarResource;
    }
}

bool Character::isMaxResourceNotReach(int resource)
{
    return resource <= 9;
}



