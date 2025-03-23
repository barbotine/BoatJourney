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
#include "FishManager.h"

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

    Texture bg, cloudText1, cloudText2, sunText, boatTexture, characterTexture, solarEnergyTexture, heartTexture, sharkTexture, fishTexture1, foodSupplyTexture;
    if (!bg.loadFromFile("../assets/texture/bg.jpg") ||
        !cloudText1.loadFromFile("../assets/texture/cloud1.png") ||
        !cloudText2.loadFromFile("../assets/texture/cloud2.png") ||
        !sunText.loadFromFile("../assets/texture/sun.png") ||
        !boatTexture.loadFromFile("../assets/texture/boat.png") ||
        !characterTexture.loadFromFile("../assets/texture/sailor.png") ||
        !solarEnergyTexture.loadFromFile("../assets/texture/solarEnergy.png") ||
        !heartTexture.loadFromFile("../assets/texture/heart.png") ||
        !sharkTexture.loadFromFile("../assets/texture/shark.png") ||
        !fishTexture1.loadFromFile("../assets/texture/fish.png") ||
        !foodSupplyTexture.loadFromFile("../assets/texture/foodSupply.png")
        ) {
        throw "Can't load";
    }

    Texture fishTexture2, fishTexture3, fishTexture4, fishTexture5, fishTexture6;
    if (!fishTexture2.loadFromFile("../assets/texture/nemo.png") ||
        !fishTexture3.loadFromFile("../assets/texture/dory.png") ||
        !fishTexture4.loadFromFile("../assets/texture/horse-lion.png") ||
        !fishTexture5.loadFromFile("../assets/texture/fish2.png") ||
        !fishTexture6.loadFromFile("../assets/texture/fish4.png") 
        )
    {
        throw "Can't load";
    }

        sf::Shader shader;
        if (!initializeShader(shader, "../assets/shaders/water_shader.frag", sf::Vector2f(window.getSize()), bg)) {
            throw "Can't load shader texture";
        }

        Clock clock;
        float currentTime = 0.0f;
        float previousTime = 0.0f;
        float deltaTime = 0.0f;

        Button solarActivityButton = Button(900, 900, 150, 50, Color::Blue, "Solar recharge");
        CloudManager cloudService = CloudManager();
        vector<Cloud> clouds = cloudService.createClouds(cloudText1, cloudText2);

        FishManager fishService = FishManager();
        vector<Fish> fishes = fishService.createFishes(fishTexture1, fishTexture2, fishTexture3, fishTexture4, fishTexture5, fishTexture6);

        Character character = Character(Vector2f(1800.f, 780.f), characterTexture);
        Boat boat = Boat(Vector2f(0.f, 0.f), boatTexture);
        Sun sun = Sun(Vector2f(100, 500.f), sunText, 250.f);
        Resource solarEnergy = Resource(Vector2f(1750.f, 780.f), solarEnergyTexture, Vector2f(1750.f, 780.f), character.getSolarResource());
        Resource lifespan = Resource(Vector2f(1750.f, 850.f), heartTexture, Vector2f(1750.f, 850.f), character.getLifespan());
        Resource foodSupply = Resource(Vector2f(1750.f, 900.f), foodSupplyTexture, Vector2f(1750.f, 950.f), character.getFoodSupply());
        Shark shark = Shark(Vector2f(1700, 450.f), sharkTexture, 300.f);

        bool collisionDetected = false;
        
        while (window.isOpen())
        {
            previousTime = currentTime;
            currentTime = clock.getElapsedTime().asSeconds();
            deltaTime = currentTime - previousTime;

            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            if (solarActivityButton.isClicked(window)) {
                character.makingSolarEnergy(sun, window);
                solarEnergy.setText(character.getSolarResource());
            }


            if (shark.getSprite().getGlobalBounds().findIntersection(boat.getSprite().getGlobalBounds()))
            {
                if (!collisionDetected)
                {
                    character.losingLifeSpan();
                    lifespan.setText(character.getLifespan());
                    collisionDetected = true;
                }
            }
            else {
                collisionDetected = false;
            }

            for (Fish& fish : fishes)
            {
                if(Utils::isClicked(fish.getSprite(), window, fish.getWasClicked()))
                {
                    character.gettingFish();
                    foodSupply.setText(character.getFoodSupply());
                    fish.makeFishDisappear(currentTime);
                }
            }

            updateShaderUniforms(shader, currentTime);

            Vector2f resolution(window.getSize().x, window.getSize().y);

            float boatX = boat.getPosition().x / resolution.x;
            boat.setOriginToBottomCenter();
            float waveHeight = seaService.calculateWaveHeight(boatX, currentTime);

            boat.setPosition(Vector2f(boatX + (resolution.x / 2.f), boat.getPosition().y + (resolution.y / 2.f) + waveHeight * resolution.y));

            window.clear();
            window.draw(background, &shader);
            solarActivityButton.draw(window);

            boat.draw(window);
            
            shark.update(window, deltaTime);
            shark.draw(window);
            
            sun.update(window, deltaTime);
            sun.draw(window);

            for (Cloud& cloud : clouds)
            {
                cloud.update(window);
                cloud.draw(window);
            }

            for (Fish& fish : fishes)
            {
                fish.update(window, currentTime, deltaTime);
                fish.draw(window);
            }

            character.draw(window);
            solarEnergy.draw(window);
            lifespan.draw(window);
            foodSupply.draw(window);

            window.display();
        }
        return 0;
    }