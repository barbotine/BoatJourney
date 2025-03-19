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
		Actor(Vector2f position, string& actorTex);
		Actor(Vector2f position, Texture& actorTex);
		virtual void update(float deltaTime);
		Vector2f getPosition();
		void draw(RenderWindow& window);
		void setPosition(Vector2f position);
		void setOriginToCenterSpriteOrigin();
		void setOriginToBottomCenter();
		bool isInsideWindowFromRight(RenderWindow& window);
		bool isInsideWindowFromLeft(RenderWindow& window);
		virtual ~Actor() = default;
};

