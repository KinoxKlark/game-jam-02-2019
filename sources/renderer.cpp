#include "renderer.h"

#include <cstdio>

void render(GameData const& data, sf::RenderWindow& window, Inputs const& inputs)
{
	// TODO(Sam): Fair un vrai syst�me d'asset
	sf::CircleShape circle(50);
	circle.setOrigin(50,50);
	circle.setFillColor(sf::Color::Red);

	// TODO(Sam): Mettre �a au bon endroit
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/ConnectionII.otf"))
	{
		return;
	}

	char debug_string[100];
	std::sprintf(debug_string, "FPS: %f\nDirection.x = %f\nDirection.y = %f",
				 1000.f/data.debug_infos.frame_length_milliseconds,
				 inputs.direction.x,
				 inputs.direction.y);
    sf::Text text(debug_string, font, 18);
	text.setFillColor(sf::Color::Black);

	circle.setPosition(data.player.pos.x,data.player.pos.y);
	// end tmp


	window.clear(sf::Color::White);
	
	// Le rendu va ici...
	window.draw(circle);

	window.draw(text);
	
	window.display();
	
	return;
}
