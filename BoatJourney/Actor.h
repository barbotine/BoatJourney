#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Actor
{

	protected:
		Vector2f position;
		Sprite sprite;
		Texture texture;

	public:
		Actor(RenderWindow& window, Vector2f position, string actorTex);

		virtual void update(float deltaTime) = 0;
		void draw(RenderWindow& window);
		void centerSpriteOrigin(Sprite& sprite);
		virtual ~Actor() = default;
};

