
#include "Item.h"

Item::Item(sf::Vector2<int> pos) {
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
}
void Item::update(sf::Vector2<int> pos) {

	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);

}
sf::Vector2<int> Item::getPos() {
	return sf::Vector2<int>(sprite.getPosition().x, sprite.getPosition().y);
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



Item* ItemSpawner::i_prototypes[] = { new Spirit, new Soda };