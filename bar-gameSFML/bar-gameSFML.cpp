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

typedef struct {
    bool focusedCollision;
    bool unfocusedCollision;
} GlassCollisionState;


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
    GlassCollisionState glassCollisionState;
    glassCollisionState.focusedCollision = false;
    glassCollisionState.unfocusedCollision = false;


    sf::Event event;
    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!minigameActivated) {

                    
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
                            //collison layering logic for glasses
                            //TODO: refactoring
                            std::list<Glass*>::iterator y = glasses.begin();
                            for (auto x{ glasses.begin() }; x != glasses.end(); ++x) {
                                if ((*x)->mouseCollision(sf::Mouse::getPosition(window))) {
                                    if (x != glasses.begin()) {
                                        y = x;
                                        glassCollisionState.unfocusedCollision = true;
                                    }
                                    else {
                                        glassCollisionState.focusedCollision = true;
                                    }
                                }
                            }
                            if (glassCollisionState.unfocusedCollision) {
                                Glass* temp = *y;
                                glasses.erase(y);
                                glasses.push_front(temp);
                                glassSelected = *(glasses.begin());
                                glassCollisionState.unfocusedCollision = false;
                            }
                            if (glassCollisionState.focusedCollision) {
                                glassSelected = *(glasses.begin());
                                glassCollisionState.focusedCollision = false;
                            }
                        }
                        
                    }
                    else {
                        minigameActivated->pressed();

                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (itemSelected) {
                        for (Glass* x : glasses) {
                            
                            if (x->mouseCollision(itemSelected->getPos())) {
                                x->add(10, itemSelected);
                                minigameActivated = new FillingMiniGame(sf::Mouse::getPosition(), 0.1f);
                                free(itemSelected);
                                //itemSelected = NULL;
                            }
                                                   
                        }
                        itemSelected = NULL;
                        
                    }
                    if (glassSelected) {
                        if (person.isColliding(glassSelected->getPos().x, glassSelected->getPos().y)) {
                            std::cout << "removed Glass" << std::endl;
                            glasses.remove(glassSelected);
                        }
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
        


        if (itemSelected) {
            itemSelected->draw(window);
        }

        //todo: implement actually working minigame dickhead
        if (minigameActivated) {
            window.setMouseCursorVisible(false);

            minigameActivated->draw(window);
            
            if (minigameActivated->update()) {
                window.setMouseCursorVisible(true);
                minigameActivated = NULL;
            }
        }
        
        window.display();
    }
}

