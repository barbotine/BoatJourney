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
#include "ProgressBar.h"
#include "HungerBar.h"

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

        Vector2f resolution(window.getSize().x, window.getSize().y);

        Clock clock;
        float currentTime = 0.0f;
        float previousTime = 0.0f;
        float deltaTime = 0.0f;

        Button solarActivityButton = Button(900, 900, 150, 50, Color::Blue, "Solar recharge");
        Button eatingActivityButton = Button(700, 900, 150, 50, Color::Blue, "Eating");
        CloudManager cloudService = CloudManager();
        vector<Cloud> clouds = cloudService.createClouds(cloudText1, cloudText2);

        FishManager fishService = FishManager();
        vector<Fish> fishes = fishService.createFishes(fishTexture1, fishTexture2, fishTexture3, fishTexture4, fishTexture5, fishTexture6);

        Character character = Character(Vector2f(1800.f, 780.f), characterTexture);
        Boat boat = Boat(Vector2f(resolution.x / 2.f, 0.f), boatTexture);
        boat.setOriginToBottomCenter();
        Sun sun = Sun(Vector2f(100, 500.f), sunText, 250.f);
        Resource solarEnergy = Resource(Vector2f(1750.f, 780.f), solarEnergyTexture, Vector2f(1750.f, 780.f), character.getSolarResource());
        Resource lifespan = Resource(Vector2f(1750.f, 850.f), heartTexture, Vector2f(1750.f, 850.f), character.getLifespan());
        Resource foodSupply = Resource(Vector2f(1750.f, 900.f), foodSupplyTexture, Vector2f(1750.f, 950.f), character.getFoodSupply());
        Shark shark = Shark(Vector2f(1900.f, 700.f), sharkTexture, 300.f);

        HungerBar hungerBar(50, 50);

        bool SharkBoatCollisionDetected = false;
        int sharkClicks = 0;
        const int sharkMaxClicks = 5;
        bool isSharkAlive = true;
        bool wasSharkPressed = false;
        
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

            if (solarActivityButton.isClicked(window)) 
            {
                character.makingSolarEnergy(sun, window);
                solarEnergy.setText(character.getSolarResource());
            }

            if (eatingActivityButton.isClicked(window)) 
            {
                character.Eat();
                foodSupply.setText(character.getFoodSupply());
                if (character.getFoodSupply() > 0)
                {
                    hungerBar.FillTheBar();
                }
            }

            if (shark.getSprite().getGlobalBounds().findIntersection(boat.getSprite().getGlobalBounds()))
            {
                if (!SharkBoatCollisionDetected)
                {
                    character.losingLifeSpan();
                    lifespan.setText(character.getLifespan());
                    SharkBoatCollisionDetected = true;
                    boat.getSprite().setColor(Color::Red);
                }
            }
            else {
                SharkBoatCollisionDetected = false;
                boat.getSprite().setColor(sf::Color::White);
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

            if (isSharkAlive && Utils::isClicked(shark.getSprite(), window, wasSharkPressed)) {
                sharkClicks++;
                if (sharkClicks >= sharkMaxClicks) {
                    shark.makeSharkDisappear(currentTime);
                    sharkClicks = 0;
                }
            }
            hungerBar.EmptyTheBar(deltaTime);

            shark.makeSharkAppear(currentTime);

            updateShaderUniforms(shader, currentTime);

            float boatX = boat.getPosition().x / resolution.x;

            float waveHeight = seaService.calculateWaveHeight(boat.getSprite().getPosition().x, currentTime);
            
            boat.setPosition(Vector2f(boat.getSprite().getPosition().x, (waveHeight + 0.5f) * resolution.y));
            window.clear();
            window.draw(background, &shader);
            
            boat.draw(window);
            
            if (shark.getIsActive()) {
                shark.update(window, deltaTime, boat);
                shark.draw(window);
            }
            
            sun.update(window, deltaTime);
            sun.draw(window);

            for (Cloud& cloud : clouds)
            {
                cloud.update(window, deltaTime);
                cloud.draw(window);
            }

            for (Fish& fish : fishes)
            {
                fish.update(window, currentTime, deltaTime);
                fish.draw(window);
            }
            hungerBar.update(hungerBar.GetCurrentHunger(), hungerBar.GetMaxHunger());
            hungerBar.draw(window);
            character.draw(window);
            solarEnergy.draw(window);
            lifespan.draw(window);
            foodSupply.draw(window);
            solarActivityButton.draw(window);
            eatingActivityButton.draw(window);
            window.display();
        }
        return 0;
    }