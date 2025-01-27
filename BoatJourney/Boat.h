#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Boat : public Actor
{
	private:
		Vector2f position;

	public:
		void update(float deltaTime) override;
		void draw(RenderWindow& window);
};

