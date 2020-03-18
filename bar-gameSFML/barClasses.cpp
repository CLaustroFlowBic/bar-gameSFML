#include <iostream>
#include "barClasses.h"


Drawable::Drawable(sf::Vector2<int> pos) {
	sprite.setPosition(pos.x, pos.y);
}

void Drawable::draw(sf::RenderWindow &window) {

	window.draw(sprite);
}


Person::Person(sf::Vector2<int> pos) : Drawable(pos) {
	image.loadFromFile("resources/sprites/guy1.png");
	sprite.setTexture(image);
	
}

bool Person::isColliding(int x, int y) {

	if (sprite.getGlobalBounds().contains(x, y)) {
		return true;
	}
	else {
		return false;
	}

}

