#include "barClasses.h"


class FillingMiniGame  {

	sf::RectangleShape border;
	sf::RectangleShape cursor;
public:
	FillingMiniGame(sf::Vector2<int> pos);
	void draw(sf::RenderWindow &window);
	bool update();
};