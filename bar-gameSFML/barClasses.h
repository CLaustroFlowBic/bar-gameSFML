#pragma once
#ifndef BARCLASSES_H
#define BARCLASSES_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

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
	std::map<std::string, int> order;
	std::string promptString;
	sf::Font font;
	sf::Text prompt;
public:
	Person(sf::Vector2<int> pos, std::map<std::string, int> _order);
	bool isColliding(int x, int y);
	bool orderChecker(std::map<std::string, int> drink);
	std::string getOrder();
	void draw(sf::RenderWindow& window);
};






#endif