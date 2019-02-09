#include "renderer.h"

void render(GameData const& data, sf::RenderWindow& window)
{
	sf::CircleShape circle(50);
	circle.setOrigin(50,50);
	circle.setFillColor(sf::Color::Red);

	circle.setPosition(data.player.pos.x,data.player.pos.y);

	window.clear(sf::Color::White);
	
	// Le rendu va ici...
	window.draw(circle);


	
	
	window.display();
	
	return;
}
