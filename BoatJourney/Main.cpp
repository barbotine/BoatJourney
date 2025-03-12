#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Cloud.h"
#include "Boat.h"
#include "Sun.h"
#include "CloudManager.h"
#include "SeaManager.h"
#include "Button.h"
#include "Character.h"
#include "Resource.h"
#include "Shark.h"
#include "Fish.h"
#include "Utils.h"

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

    Texture bg, cloudText1, cloudText2, sunText, boatTexture, characterTexture, solarEnergyTexture, heartTexture, sharkTexture, fishTexture, foodSupplyTexture;
    if (!bg.loadFromFile("../assets/texture/bg.jpg") ||
        !cloudText1.loadFromFile("../assets/texture/cloud1.png") ||
        !cloudText2.loadFromFile("../assets/texture/cloud2.png")|| 
        !sunText.loadFromFile("../assets/texture/sun.png") ||
        !boatTexture.loadFromFile("../assets/texture/boat.png") ||
        !characterTexture.loadFromFile("../assets/texture/sailor.png") ||
        !solarEnergyTexture.loadFromFile("../assets/texture/solarEnergy.png") ||
        !heartTexture.loadFromFile("../assets/texture/heart.png") ||
        !sharkTexture.loadFromFile("../assets/texture/shark.png") || 
        !fishTexture.loadFromFile("../assets/texture/fish.png") ||
        !foodSupplyTexture.loadFromFile("../assets/texture/foodSupply.png")
        ) {
        throw "Can't load";
    }
    
    sf::Shader shader;
    if (!initializeShader(shader, "../assets/shaders/water_shader.frag", sf::Vector2f(window.getSize()), bg)) {
        throw "Can't load shader texture";
    }
    Clock clock;
    float time = clock.getElapsedTime().asSeconds();

    Button solarActivityButton = Button(900, 900, 150, 50, Color::Blue, "Solar Panel");
    CloudManager cloudService = CloudManager();
    vector<Cloud> clouds = cloudService.createClouds(cloudText1, cloudText2);
    Character character = Character(Vector2f(1800.f, 780.f), characterTexture);
    Boat boat = Boat(Vector2f(0.f, 0.f), boatTexture);
    Sun sun = Sun(Vector2f(100, 500.f), sunText, 0.2f);
    Resource solarEnergy = Resource(Vector2f(1750.f, 780.f), solarEnergyTexture, Vector2f(1750.f, 780.f), character.getSolarResource());
    Resource lifespan = Resource(Vector2f(1750.f, 850.f), heartTexture, Vector2f(1750.f, 850.f), character.getLifespan());
    Resource foodSupply = Resource(Vector2f(1750.f, 900.f), foodSupplyTexture, Vector2f(1750.f, 950.f), character.getFoodSupply());
    Shark shark = Shark(Vector2f(1700, 500.f), sharkTexture, 0.5f);
    Fish fish = Fish(Vector2f(1700, 700.f), fishTexture, 0.2f, MovementDirection::RIGHT);
    
    while(window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (solarActivityButton.isClicked(window)) {
            character.makingSolarEnergy(sun, window);
            solarEnergy.setText(character.getSolarResource());
        }

        if (Utils::isClicked(fish.getSprite(), window, fish.getWasClicked()))
        {
                character.gettingFish();
                cout << "cliqué" << endl;
                foodSupply.setText(character.getFoodSupply());
        }

        time = clock.getElapsedTime().asSeconds();
      
        updateShaderUniforms(shader, time);

        Vector2f resolution(window.getSize().x, window.getSize().y);
     
        float boatX = boat.getPosition().x / resolution.x;
        boat.setOriginToBottomCenter();
        float waveHeight = seaService.calculateWaveHeight(boatX, time);

        boat.setPosition(Vector2f(boatX + (resolution.x / 2.f), boat.getPosition().y + (resolution.y / 2.f) + waveHeight * resolution.y));

        window.clear();
        window.draw(background, &shader);
        solarActivityButton.draw(window);

        boat.draw(window);
        character.draw(window);
        solarEnergy.draw(window);
        lifespan.draw(window);
        
        foodSupply.draw(window);
        shark.update(window);
        shark.draw(window);

        fish.update(window);
        fish.draw(window);

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