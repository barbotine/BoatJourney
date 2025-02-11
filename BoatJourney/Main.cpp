#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "Cloud.h"
#include "Boat.h"
#include "Sun.h"

using namespace std;
using namespace sf;

float wave(float x, float frequency, float amplitude, float speed, float phase, float time) {
    return sin(x * frequency + time * speed + phase) * amplitude;
}

float calculateWaveHeight(float x, float time) {
    float y = 0.0;

    y += wave(x, 10.0, 0.03, 2.0, 0.0, time);
    y += wave(x, 15.0, 0.02, 3.0, 1.0, time);
    y += wave(x, 20.0, 0.01, 1.5, 2.0, time);

    return y;
}

int main()
{
    VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.size.x;
    unsigned int screenHeight = desktopMode.size.y;

    RenderWindow window(desktopMode, "Plein écran");

    RectangleShape background(sf::Vector2f(window.getSize()));
    Vector2f backgroundPosition(0.f, 0.f);
    background.setPosition(backgroundPosition);
    Vector2f positionSun;


    sf::Texture bg, cloudText1, cloudText2, sunText;
    if (!bg.loadFromFile("../assets/texture/bg.jpg") ||
        !cloudText1.loadFromFile("../assets/texture/cloud.png") ||
        !cloudText2.loadFromFile("../assets/texture/cloud3.png")|| 
        !sunText.loadFromFile("../assets/texture/sun.png")) {
        return -1;
    }
    vector<Cloud> clouds;
    Cloud cloud = Cloud(Vector2f(0.f, 0.f), cloudText1, 0.5);
    Cloud cloud2 = Cloud(Vector2f(500.f, 0.f), cloudText2, 0.5);
    Cloud cloud3 = Cloud(Vector2f(900.f, 0.f), cloudText1, 0.5);
    Cloud cloud4 = Cloud(Vector2f(1400.f, 0.f), cloudText2, 0.5);
    
    clouds.push_back(cloud);
    clouds.push_back(cloud2);
    clouds.push_back(cloud3);
    clouds.push_back(cloud4);

    vector<Sun> suns;
    Sun sun = Sun(Vector2f(0.f, 0.f), sunText, 0.3);
    suns.push_back(sun);
    

    sf::Shader shader;
    if (!shader.loadFromFile("../assets/shaders/water_shader.frag", sf::Shader::Type::Fragment)) {
        std::cerr << "Erreur lors du chargement du shader !" << std::endl;
        return -1;
    }
    
    Color color = sf::Color::Blue;
    Clock clock;

    float time = clock.getElapsedTime().asSeconds();
    
    while(window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        time = clock.getElapsedTime().asSeconds();
      
        shader.setUniform("time", time);
        shader.setUniform("resolution", sf::Vector2f(window.getSize()));
        shader.setUniform("backgroundTex", bg);

        Vector2f resolution(window.getSize().x, window.getSize().y);
     
        Boat boat = Boat(Vector2f(0.f, 0.f), "../assets/texture/boat.png");
        Sun sun = Sun(Vector2f(0, 0.f), sunText, 0.2);
        boat.centerSpriteOrigin();
        sun.centerSpriteOrigin();
        float boatX = boat.getPosition().x / resolution.x;
        float waveHeight = calculateWaveHeight(boatX, time);

        boat.setPosition(Vector2f(boatX + 700, (resolution.y / 2.f) + waveHeight * (resolution.y + 400)));

        window.clear();
        window.draw(background, &shader);
       
        boat.draw(window);
        
        for (Sun& sun : suns)
        {
            sun.update(window);
            sun.draw(window);
        }

        for (Cloud& cloud : clouds)
        {
            cloud.update(window);
            cloud.draw(window);
        }

      
        window.display();
    }  
    return 0; 
}