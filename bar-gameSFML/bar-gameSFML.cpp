#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

#include "barClasses.h"
#include "Item.h"
#include "Glass.h"
#include "FillingMinigame.h"


//main file for this project

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Bar-Game");

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
    std::list<Glass*> glasses;
    
    int glassid = 0;
    bool collision = false;
    
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
                    
                    //might be able to get rid of this
                    for (GlassSpawner x : GlassSpawnerCollisions) {
                        if (x.mouseCollision(sf::Mouse::getPosition(window))) {
                            glassSelected = x.spawn(sf::Mouse::getPosition(window), glassid);
                            glasses.insert(glasses.begin(), glassSelected);
                            glassid++;

                        }
                    }
                    
                    if (!glasses.empty()) {
                        
                        std::list<Glass*>::iterator y = glasses.begin();;
                        for (auto x{ glasses.begin() }; x != glasses.end(); ++x) {
                            if ((*x)->mouseCollision(sf::Mouse::getPosition(window))) {

                               
                                if (x != glasses.begin()) {
                                    y = x;
                                    collision = true;
                                }
                                
                            }

                            
                        }
                        if (collision) {
                            Glass* temp = *y;
                            glasses.erase(y);
                            glasses.push_front(temp);
                            glassSelected = *(glasses.begin());
                            collision = false;
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
                                minigameActivated = new FillingMiniGame(sf::Mouse::getPosition());
                                free(itemSelected);
                                //itemSelected = NULL;
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

        
        for (Drawable x : drawList) {
            x.draw(window);
        }
        /*for (Glass* x : glasses) {
            x->draw(window);
        }*/

        
        for (auto p{ glasses.rbegin() }; p != glasses.rend(); ++p) {
            //std::cout << (*p)->id << ",";
            (*p)->draw(window);
        }
        std::cout << std::endl;


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

