#pragma once
#ifndef BARCLASSES_H
#define BARCLASSES_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

const int numberOfItems = 3;


class Drawable {

public:
	Drawable() {};
	Drawable(sf::Vector2<int> pos);
	void draw(sf::RenderWindow& window);

protected:

	sf::Texture image;
	sf::Sprite sprite;
	sf::Vector2<int> position;
};

class Person : public Drawable {

public:
	Person(sf::Vector2<int> pos);
};

//Base class for Item Objects
class Item : public Drawable {
public:
	Item() {};
	Item(sf::Vector2<int> pos);
	virtual Item* clone(sf::Vector2<int> pos) = 0 ;
	void update(sf::Vector2<int> pos);
	
};

//Spirit Item Object
class Spirit : public Item {
public:
	Spirit() {};
	Spirit(sf::Vector2<int> pos);
	Item* clone(sf::Vector2<int> pos) { return new Spirit(pos); }
	void getName();  
};

//Soda Item Objects
class Soda : public Item {
public:
	Soda() {};
	~Soda() {};
	Soda(sf::Vector2<int> pos);
	Item* clone(sf::Vector2<int> pos) { return new Soda(pos); }

	
};
class OldFashioned : public Item {
public:
	OldFashioned() {};
	OldFashioned(sf::Vector2<int> pos);
	Item* clone(sf::Vector2<int> pos) { return new OldFashioned(pos); }
};

//Factory style Class for Item objects
class Spawner : public Drawable {
private: 
	static Item* i_prototypes[numberOfItems];
	int choice;

public:
	Spawner(sf::Vector2<int> pos, std::string spritePath, int _choice) : Drawable(pos) {
		image.loadFromFile(spritePath);
		sprite.setTexture(image);
		choice = _choice;

	}
	bool mouseCollision(sf::Vector2<int> pos) {
		if (sprite.getGlobalBounds().contains(pos.x , pos.y)) {
			return true;
			
		}
		else
			return false;
	}
	Item* spawn(sf::Vector2<int> pos) {

		return i_prototypes[choice]->clone(pos);
	};
};




#endif