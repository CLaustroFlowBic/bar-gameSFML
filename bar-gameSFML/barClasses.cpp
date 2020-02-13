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

Item::Item(sf::Vector2<int> pos) {
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
}
void Item::update(sf::Vector2<int> pos) {

	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
	
}


Spirit::Spirit(sf::Vector2<int> pos) : Item(pos) {
	image.loadFromFile("resources/sprites/vodka.png");
	sprite.setTexture(image);
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
}

Soda::Soda(sf::Vector2<int> pos) : Item(pos) {
	image.loadFromFile("resources/sprites/soda.jpg");
	sprite.setTexture(image);
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
}
OldFashioned::OldFashioned(sf::Vector2<int> pos) : Item(pos) {
	image.loadFromFile("resources/sprites/glass1.jpg");
	sprite.setTexture(image);
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
}


Item* Spawner::i_prototypes[] = { new Spirit, new Soda, new OldFashioned };




