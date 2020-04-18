#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <time.h>

#include "barClasses.h"
#include "Item.h"
#include "Glass.h"
#include "FillingMinigame.h"


/*

1: Rum & Coke
2: Gin & Tonic
3. Vodka & Coke


*/

//main file for this project

typedef struct {
    bool focusedCollision;
    bool unfocusedCollision;
} GlassCollisionState;

typedef struct {
    Item* itemFill;
    Glass* glassFill;

} AddItemToGlass;

typedef struct {
    sf::Texture texture;
    sf::Sprite sprite;
} SodaGun;

typedef struct {
    sf::Texture texture;
    sf::Sprite sprite;
} BarTop;

//generates a customers order
std::string genOrder(int selection, int& amount) {

    switch (selection) {
    case 0:
        amount = 50;
        return "vodka";
    case 1:
        amount = 50;
        return "gin";
    case 2:
        amount = 50;
        return "darkrum";
    case 3:
        amount = 50;
        return "coke";
    }
    return "";
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Bar-Game");
    window.setFramerateLimit(60);
    std::string spritePath = "resources/sprites/";
    
    ItemSpawner spiritSpawner(sf::Vector2<int>(200, 500), spritePath + "vodka.png", "vodka");
    ItemSpawner darkRum(sf::Vector2<int>(250, 500), spritePath + "darkrum.png", "darkrum");
    ItemSpawner gin(sf::Vector2<int>(300, 500), spritePath + "gin.png", "gin");
    
    ItemSpawner coke(sf::Vector2<int>(700, 500), spritePath + "soda-gun/sodaGun.png", "coke");
    ItemSpawner water(sf::Vector2<int>(700, 600), spritePath + "soda-gun/sodaGun.png", "water");
    ItemSpawner sprite(sf::Vector2<int>(750, 500), spritePath + "soda-gun/sodaGun.png", "lemonade");
    ItemSpawner sodaWater(sf::Vector2<int>(700, 550), spritePath + "soda-gun/sodaGun.png", "soda-water");
    ItemSpawner tonicWater(sf::Vector2<int>(750, 550), spritePath + "soda-gun/sodaGun.png", "tonic-water");
   

    std::vector<ItemSpawner> sodaGunDrinks{ coke, sprite, sodaWater, tonicWater, water };

    SodaGun sodaGun;
    sodaGun.texture.loadFromFile(spritePath + "soda-gun/sodaGun.png");
    sodaGun.sprite.setTexture(sodaGun.texture);
    sodaGun.sprite.setPosition(700, 500);

    BarTop barTop;
    barTop.texture.loadFromFile(spritePath + "bartop.png");
    barTop.sprite.setTexture(barTop.texture);
    barTop.sprite.setPosition(175, 300);

    std::vector<ItemSpawner> itemSpawnerCollisions{ spiritSpawner, darkRum, gin, coke, sprite, sodaWater, tonicWater, water };
        
    GlassSpawner oldFashionedSpawner(sf::Vector2<int>(600, 585), spritePath + "rocks_empty.png", 0);
    std::vector<GlassSpawner> GlassSpawnerCollisions{ oldFashionedSpawner };

    srand(time(NULL));
    std::list<Person> personStack;

    //TODO: find a better way to do this
    for (int i = 0; i < 20; ++i) {
        int amount1 = 0;
        int amount2 = 0;        
        std::map<std::string, int> temp;

        temp.insert(std::pair<std::string, int>(genOrder(rand() % 4, amount1) , amount1));
        temp.insert(std::pair<std::string, int>(genOrder(rand() % 4, amount2) , amount2));

        Person *person = new Person(sf::Vector2<int>(590, 100),  temp);
        personStack.push_back((*person));
        temp.clear();        
    }    
    
    //copy both collision maybe a lil faster
    std::vector<Drawable> drawList{ spiritSpawner, oldFashionedSpawner, darkRum, gin};
    
    //Used when user grabs an item/glass
    Item* itemSelected = NULL;
    Glass* glassSelected = NULL;

    //these two are used as fill state captures, they are used as a side effect of the way the
    //cursor in the minigame updates
    AddItemToGlass addItemToGlass;
    addItemToGlass.glassFill = NULL;
    addItemToGlass.itemFill = NULL;

    FillingMiniGame* minigameActivated = NULL;
    
    std::list<Glass*> glasses;
    int glassid = 0;

    //state machine for glass focus state
    GlassCollisionState glassCollisionState;
    glassCollisionState.focusedCollision = false;
    glassCollisionState.unfocusedCollision = false;

    sf::Clock clock;

    sf::Event event;
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        while (window.pollEvent(event)) {
            //Exiting
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    //if not in a minigame continue as normal
                    if (!minigameActivated) {

                        for (ItemSpawner x : itemSpawnerCollisions) {
                            if (x.mouseCollision(sf::Mouse::getPosition(window))) {
                                itemSelected = x.spawn(sf::Mouse::getPosition(window));
                            }
                        }

                        

                        //might be able to get rid of this maybe add these two into some base class maybe??
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
                            //finds a collided glass
                            for (auto x { glasses.begin() }; x != glasses.end(); ++x) {
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
                            //processing glass collision
                            //potentially refactor into own function
                            if (glassCollisionState.unfocusedCollision) {
                                Glass* temp = *y;
                                glasses.erase(y);
                                glasses.push_front(temp);
                                glassSelected = *(glasses.begin());
                                glassSelected->update(sf::Mouse::getPosition(window));
                                glassCollisionState.unfocusedCollision = false;
                            }
                            if (glassCollisionState.focusedCollision) {
                                glassSelected = *(glasses.begin());
                                glassSelected->update(sf::Mouse::getPosition(window));
                                glassCollisionState.focusedCollision = false;
                            }
                        }
                        
                    }
                    //if in a minigame check if the mouse has been pressed
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
                                
                                minigameActivated = new FillingMiniGame(sf::Mouse::getPosition(), 80.0f);
                                addItemToGlass.glassFill = x;
                                addItemToGlass.itemFill = itemSelected;
                                
                                //free(itemSelected);
                                //itemSelected = NULL;
                            }
                                                   
                        }
                        itemSelected = NULL;
                        
                    }
                    if (glassSelected) {
                        if (personStack.front().isColliding(glassSelected->getPos().x, glassSelected->getPos().y)) {
                            std::cout << "removed Glass" << std::endl;
                            std::cout << personStack.front().getOrder() << std::endl;
                            glasses.remove(glassSelected);
                            if (personStack.front().orderChecker(glassSelected->getContents())) {
                                personStack.pop_front();
                            }
                            
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

        window.draw(barTop.sprite); 

        personStack.front().draw(window);
        for (Drawable x : drawList) {
            x.draw(window);
        }
        
        for (auto p{ glasses.rbegin() }; p != glasses.rend(); ++p) {
            //std::cout << (*p)->id << ",";
            (*p)->draw(window);
        }
        
        window.draw(sodaGun.sprite);

        

        if (itemSelected) {
            itemSelected->draw(window);
        }
       // std::cout << dt.asMilliseconds() << std::endl;
        //todo: implement actually working minigame dickhead
        if (minigameActivated) {
            window.setMouseCursorVisible(false);

            minigameActivated->draw(window);
            if (minigameActivated->update(dt.asSeconds())) {
                window.setMouseCursorVisible(true); 
                addItemToGlass.glassFill->add(minigameActivated->getAmountFilled(), addItemToGlass.itemFill);
                delete minigameActivated;
                minigameActivated = NULL;
            }
        }
        
        window.display();
        
    }
}

