#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Cloud.h"
#include "Boat.h"
#include "Sun.h"
#include "CloudManager.h"
#include "SeaManager.h"

using namespace std;
using namespace sf;

bool initializeShader(sf::Shader& shader, const string& shaderFilePath, const sf::Vector2f& resolution, sf::Texture& bgTexture) {
    if (!shader.loadFromFile(shaderFilePath, sf::Shader::Type::Fragment)) {
        throw "Can't load shader";
    }
    shader.setUniform("resolution", resolution);
    shader.setUniform("backgroundTex", bgTexture);
    return true;
}

void updateShaderUniforms(sf::Shader& shader, float time) {
    shader.setUniform("time", time);
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

    SeaManager seaService = SeaManager();

    Texture bg, cloudText1, cloudText2, sunText, boatTexture;
    if (!bg.loadFromFile("../assets/texture/bg.jpg") ||
        !cloudText1.loadFromFile("../assets/texture/cloud.png") ||
        !cloudText2.loadFromFile("../assets/texture/cloud3.png")|| 
        !sunText.loadFromFile("../assets/texture/sun.png") ||
        !boatTexture.loadFromFile("../assets/texture/boat.png")) {
        return -1;
    }
    CloudManager cloudService = CloudManager();
    vector<Cloud> clouds = cloudService.createClouds(cloudText1, cloudText2);
    
    sf::Shader shader;
    if (!initializeShader(shader, "../assets/shaders/water_shader.frag", sf::Vector2f(window.getSize()), bg)) {
        throw "Can't load shader texture";
    }
    Clock clock;
    float time = clock.getElapsedTime().asSeconds();

    Boat boat = Boat(Vector2f(0.f, 0.f), boatTexture);
    Sun sun = Sun(Vector2f(100, 500.f), sunText, 0.03);
    
    while(window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        time = clock.getElapsedTime().asSeconds();
      
        updateShaderUniforms(shader, time);

        Vector2f resolution(window.getSize().x, window.getSize().y);
     
        float boatX = boat.getPosition().x / resolution.x;
        boat.setOriginToBottomCenter();
        float waveHeight = seaService.calculateWaveHeight(boatX, time);

        boat.setPosition(Vector2f(boatX + (resolution.x / 2.f), boat.getPosition().y + (resolution.y / 2.f)+ waveHeight * resolution.y));

        window.clear();
        window.draw(background, &shader);
       
        boat.draw(window);
        
        sun.update(window);
        sun.draw(window);

        for (Cloud& cloud : clouds)
        {
            cloud.update(window);
            cloud.draw(window);
        }

      
        window.display();
    }  
    return 0; 
}