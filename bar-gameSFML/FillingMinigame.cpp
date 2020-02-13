#include "FillingMinigame.h"


FillingMiniGame::FillingMiniGame(sf::Vector2<int> pos) {

	border = sf::RectangleShape(sf::Vector2f(100,200));
	cursor = sf::RectangleShape(sf::Vector2f(border.getGlobalBounds().width, 5));
	border.setFillColor(sf::Color(0, 0, 0));
	border.setOutlineThickness(2);
	border.setOutlineColor(sf::Color(250, 150, 100));

	cursor.setFillColor(sf::Color(255, 0, 0));

	border.setPosition(pos.x - 200, pos.y - 250);

	cursor.setPosition(border.getPosition().x, 
					   border.getPosition().y + border.getGlobalBounds().height - cursor.getGlobalBounds().height);
	

}

void FillingMiniGame::draw(sf::RenderWindow &window) {
	window.draw(border);
	window.draw(cursor);
}

bool FillingMiniGame::update() {
	cursor.setPosition(cursor.getPosition().x, cursor.getPosition().y - 1);
	if (cursor.getPosition().y >= border.getPosition().y) {
		return false;
	}
	else {
		return true;
	}
}