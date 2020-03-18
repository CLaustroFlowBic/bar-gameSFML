#include "barClasses.h"


class FillingMiniGame  {

	sf::RectangleShape border;
	sf::RectangleShape cursor;
	bool activated;
	float speed;
public:
	FillingMiniGame(sf::Vector2<int> pos, float _speed);
	void draw(sf::RenderWindow &window);
	int getAmountFilled();
	bool update();
	void pressed();
};