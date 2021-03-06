#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <vector>
#include "barClasses.h"
#include "Item.h"
#include "Glass.h"
#include "FillingMinigame.h"


int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    std::string spritePath = "resources/sprites/";
    
    
    ItemSpawner spiritSpawner(sf::Vector2<int>(200, 200), spritePath + "vodka.png", 0);
    ItemSpawner SodaSpawner(sf::Vector2<int>(300, 300), spritePath + "soda.jpg", 1);
    std::vector<ItemSpawner> itemSpawnerCollisions{ spiritSpawner, SodaSpawner };

    GlassSpawner oldFashionedSpawner(sf::Vector2<int>(400, 400), spritePath + "glass1.jpg", 0);
    std::vector<GlassSpawner> GlassSpawnerCollisions{ oldFashionedSpawner };

    Person person(sf::Vector2<int>(100,100));
    
    std::vector<Drawable> drawList{ spiritSpawner, SodaSpawner, oldFashionedSpawner, person};
    
 
    Item* itemSelected = NULL;
    Glass* glassSelected = NULL;
    FillingMiniGame* minigameActivated = NULL;
    std::vector<Glass*> glasses;
    
    
    
    
    sf::Event event;
    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    for (ItemSpawner x : itemSpawnerCollisions) {
                        if (x.mouseCollision(sf::Mouse::getPosition(window))) {
                            
                            itemSelected = x.spawn(sf::Mouse::getPosition(window));

                        }
                    }
                    
                    for (GlassSpawner x : GlassSpawnerCollisions) {
                        if (x.mouseCollision(sf::Mouse::getPosition(window))) {
                            glassSelected = x.spawn(sf::Mouse::getPosition(window));
                            glasses.push_back(glassSelected);

                        }
                    }

                    if (!glasses.empty()) {
                        
                        for (Glass* x : glasses) {
                            
                            if (x->mouseCollision(sf::Mouse::getPosition(window))) {
                                glassSelected = x;
                            }
                        }
                        
                    }
                    
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (itemSelected) {
                        for (Glass* x : glasses) {
                            
                            if (x->mouseCollision(itemSelected->getPos())) {
                                x->add(10, itemSelected);
                                itemSelected = NULL;
                                minigameActivated = new FillingMiniGame(sf::Mouse::getPosition());
                            }
                                                   
                        }
                        itemSelected = NULL;
                        
                    }
                    if (glassSelected) {
                        glassSelected = NULL;
                    }
                }
                

            }
            if (event.type == sf::Event::MouseMoved){
                if (itemSelected) {
                    itemSelected->update(sf::Mouse::getPosition(window));
                }
                if (glassSelected) {
                    glassSelected->update(sf::Mouse::getPosition(window));
                }

            }
        }
        window.clear();

        
        for (Drawable x : drawList) 
             x.draw(window);
        for (Glass* x : glasses) {
            x->draw(window);
        }
        if (itemSelected) {
            itemSelected->draw(window);
        }
        if (minigameActivated) {
            minigameActivated->draw(window);
            if (minigameActivated->update()) {
                minigameActivated = NULL;
            }
        }
        
        window.display();
    }
}

