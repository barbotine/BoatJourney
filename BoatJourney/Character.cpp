#include "Character.h"

Character::Character(Vector2f position, Texture& texture) : Actor(position, texture)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    this->solarRessource = 0;
    this->life = 10;
    this->food = 10;
    this->water = 10;
}

bool Character::isSunInsideWindow(Sun& sun, RenderWindow& window)
{
    if(sun.getIsVisible())
    {
        cout << "Il est visible et dans la fenêtre" << endl;
    }
    else 
    {
        cout << "Il est invisible" << endl;
    }
    return sun.getIsVisible();
}

void Character::makingSolarEnergy(Sun& sun, RenderWindow& window)
{
    if (isSunInsideWindow(sun, window) && isMaxRessourceNotReach(solarRessource))
    {
        cout << "Adding solar ressource" << endl;
        ++solarRessource;
    }
}

bool Character::isMaxRessourceNotReach(int ressource)
{
    return ressource <= 9;
}


