
#include "Item.h"

Item::Item(sf::Vector2<int> pos, std::string _name, std::string spritePath) {
	image.loadFromFile(spritePath);
	sprite.setTexture(image);
	name = _name;
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
}
void Item::update(sf::Vector2<int> pos) {

	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);

}
sf::Vector2<int> Item::getPos() {
	return sf::Vector2<int>(sprite.getPosition().x, sprite.getPosition().y);
}




