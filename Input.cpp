#include "Input.h"

Input::Input() {
	init(nullptr);
}
Input::Input(Entity* parent) {
	this->parent = parent;
	init(nullptr);
}

void Input::init(sf::RenderWindow* window) {
	this->window = window;

	schemes.clear();
}

void Input::update() {
	mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void Input::addScheme(InputScheme scheme) {
	schemes.push_back(scheme);
}
void Input::setSchemes(std::vector<InputScheme> schemes) {
	this->schemes = schemes;
}
void Input::clearSchemes() {
	schemes.clear();
}

sf::Vector2f Input::getAxes() {
	// Does not allow for small joystick movements. (gets normalized on return line)
	sf::Vector2f axis;
	for (InputScheme s : schemes) {
		sf::Vector2f candidateAxis;
		switch (s) {
			case InputScheme::WASD:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) candidateAxis.y -= 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) candidateAxis.x -= 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) candidateAxis.y += 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) candidateAxis.x += 1;
				break;
			case InputScheme::ArrowKeys:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) candidateAxis.y -= 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) candidateAxis.x -= 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) candidateAxis.y += 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) candidateAxis.x += 1;
				break;
			case InputScheme::Controller1:
				if (sf::Joystick::isConnected(0)) {
					candidateAxis.x = sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.f;
					candidateAxis.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100.f;
				}
				break;
			case InputScheme::Controller2:
				if (sf::Joystick::isConnected(2)) { // 2, not 1 because two joysticks per controller
					candidateAxis.x = sf::Joystick::getAxisPosition(2, sf::Joystick::X) / 100.f;
					candidateAxis.y = sf::Joystick::getAxisPosition(2, sf::Joystick::Y) / 100.f;
				}
				break;
			case InputScheme::Controller3:
				if (sf::Joystick::isConnected(4)) {
					candidateAxis.x = sf::Joystick::getAxisPosition(4, sf::Joystick::X) / 100.f;
					candidateAxis.y = sf::Joystick::getAxisPosition(4, sf::Joystick::Y) / 100.f;
				}
				break;
			case InputScheme::Controller4:
				if (sf::Joystick::isConnected(6)) {
					candidateAxis.x = sf::Joystick::getAxisPosition(6, sf::Joystick::X) / 100.f;
					candidateAxis.y = sf::Joystick::getAxisPosition(6, sf::Joystick::Y) / 100.f;
				}
				break;
			default:
				break;
		}
		// if candidate is not untouched, overwrite
		axis += candidateAxis;
	}
	float mag = sqrtf(axis.x * axis.x + axis.y * axis.y);
	if (mag == 0) return axis;
	return axis / mag; // normalize
}

bool Input::getJump() {
	bool jump = false;
	for (InputScheme s : schemes) {
		switch (s) {
			case InputScheme::WASD:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) jump = true;
				break;
			case InputScheme::ArrowKeys:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) jump = true;
				break;
			case InputScheme::Controller1:
				if (sf::Joystick::isButtonPressed(0, 0)) jump = true;
				break;
			case InputScheme::Controller2:
				if (sf::Joystick::isButtonPressed(2, 0)) jump = true;
				break;
			case InputScheme::Controller3:
				if (sf::Joystick::isButtonPressed(4, 0)) jump = true;
				break;
			case InputScheme::Controller4:
				if (sf::Joystick::isButtonPressed(6, 0)) jump = true;
				break;
		}
	}
	return jump;
}

bool Input::getAttack() {
	bool attack = false;
	for (InputScheme s : schemes) {
		switch (s) {
		case InputScheme::WASD:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) attack = true;
			break;
		case InputScheme::ArrowKeys:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) attack = true;
			break;
		case InputScheme::Controller1:
			if (sf::Joystick::isButtonPressed(0, 1)) attack = true;
			break;
		case InputScheme::Controller2:
			if (sf::Joystick::isButtonPressed(2, 1)) attack = true;
			break;
		case InputScheme::Controller3:
			if (sf::Joystick::isButtonPressed(4, 1)) attack = true;
			break;
		case InputScheme::Controller4:
			if (sf::Joystick::isButtonPressed(6, 1)) attack = true;
			break;
		}
	}
	return attack;
}

bool Input::getSpecial() {
	bool special = false;
	for (InputScheme s : schemes) {
		switch (s) {
		case InputScheme::WASD:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) special = true;
			break;
		case InputScheme::ArrowKeys:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) special = true;
			break;
		case InputScheme::Controller1:
			if (sf::Joystick::isButtonPressed(0, 2)) special = true;
			break;
		case InputScheme::Controller2:
			if (sf::Joystick::isButtonPressed(2, 2)) special = true;
			break;
		case InputScheme::Controller3:
			if (sf::Joystick::isButtonPressed(4, 2)) special = true;
			break;
		case InputScheme::Controller4:
			if (sf::Joystick::isButtonPressed(6, 2)) special = true;
			break;
		}
	}
	return special;
}
