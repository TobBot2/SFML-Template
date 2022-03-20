#include <SFML/Graphics.hpp>
#include <iostream>

#include "World.h"
#include "Player.h"
#include "Wall.h"

// https://www.sfml-dev.org/tutorials/2.5
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
	sf::View view = window.getDefaultView(); // stores copy of view (2d camera)
	sf::Clock clock;

	World world;
	world.setGravity(600);

	// create starting entities
	Player* player1 = world.addEntity<Player>();
	player1->init(100, 250, 32, 32, &world, &window);
	player1->getComponent<Input>()->setSchemes({ Input::InputScheme::WASD });

	Player* player2 = world.addEntity<Player>();
	player2->init(600, 250, 32, 32, &world, &window);
	player2->getComponent<Input>()->setSchemes({ Input::InputScheme::ArrowKeys });
	player2->getSprite()->setFillColor(sf::Color::Blue);

	Wall* floor = world.addEntity<Wall>();
	floor->init(0, 500 - 32, 800, 32, &world);

	// only one can be enabled! Vsync OR fps limit
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					view.reset(sf::FloatRect(0.f, 0.f, (float) event.size.width, (float) event.size.height));
					window.setView(view);
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Escape:
							window.close();
							break;
					}
					break;
				default:
					break;
			}
		}

		// update
		world.update(clock.restart().asSeconds());

		// render
		window.clear();

		world.render(&window);

		window.display();
	}

	return 0;
}