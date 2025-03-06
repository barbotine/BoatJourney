#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"

using namespace sf;
using namespace std;

class Character : public Actor
{
	public:
		Character(Vector2f position, Texture& texture);
		void setSolarRessources(bool isGeneratedSolarEnergy);
		bool maxRessourcesAlllowed(int ressource);

	private:
		int solarRessource;
		int life;
		int food;
		int water;
};

