#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Actor
{

	protected:
		Sprite sprite;
		Texture texture;

	public:
		Actor(Vector2f position, string& actorTex);
		Actor(Vector2f position, Texture& actorTex);
		virtual void update(float deltaTime);
		Vector2f getPosition();
		void draw(RenderWindow& window);
		void scaleSprite(sf::Sprite& sprite, const sf::Vector2u& windowSize, const sf::Vector2f& originalResolution, bool preserveRatio);
		void setPosition(Vector2f position, Vector2u windowSize, Vector2f originalResolution);
		void setOriginToCenterSpriteOrigin();
		void setOriginToBottomCenter();
		bool isInsideWindowFromRight(RenderWindow& window);
		bool isInsideWindowFromLeft(RenderWindow& window);
		Sprite& getSprite();
		virtual ~Actor() = default;
};

