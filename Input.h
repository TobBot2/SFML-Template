#pragma once
#include "Component.h"

#include <SFML/Window.hpp>

#include <vector>
#include <functional>
class Input : public Component {
	// if doing local multiplayer, change WASD and ArrowKeys to be more comfortable
	// maybe JKL -> CVB, CXZ -> KL[Semicolon]
public:
	enum class InputScheme {
		WASD,
		ArrowKeys,
		Controller1,
		Controller2,
		Controller3,
		Controller4,
	};
	Input();
	Input(Entity* parent);
	void init(sf::RenderWindow* window);
	void update();

	void addScheme(InputScheme scheme);
	void setSchemes(std::vector<InputScheme> schemes);
	void clearSchemes();

	sf::Vector2f getAxes();
	bool getJump();
	bool getAttack();
	bool getSpecial();

private:
	sf::RenderWindow* window;

	sf::Vector2f mouseCoords;


	std::vector<InputScheme> schemes;
};