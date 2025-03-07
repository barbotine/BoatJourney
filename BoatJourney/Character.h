#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"
#include "Sun.h"

using namespace sf;
using namespace std;

class Character : public Actor
{
	public:
		Character(Vector2f position, Texture& texture);
		void makingSolarEnergy(Sun& sun, RenderWindow& window);
		bool isMaxRessourceNotReach(int ressource);

	private:
		int solarRessource;
		int life;
		int food;
		int water;
};

