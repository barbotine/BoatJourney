#include "Character.h"

Character::Character(Vector2f position, Texture& texture) : Actor(position, texture)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    this->solarResource = 0;
    this->lifespan = 3;
    this->foodSupply = 0;
    this->water = 0;
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

int Character::getSolarResource()
{
    return solarResource;
}

int Character::getLifespan()
{
    return lifespan;
}

int Character::getFoodSupply()
{
    return foodSupply;
}

void Character::gettingFish()
{
    if (isMaxResourceNotReach(foodSupply))
    {
        foodSupply++;
    }
}

void Character::losingLifeSpan()
{
    lifespan--;
    if (lifespan == 0)
    {
        cout << "You lose" << endl;
    }
}

    