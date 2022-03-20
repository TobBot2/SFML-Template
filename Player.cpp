#include "Player.h"

Player::Player() 
	: Entity::Entity() {
	movementForce = 1000;
	jumpForce = 50000;
	jumpCooldownTimer = 0;

	input = addComponent<Input>();
	phys = addComponent<Physics>();
}

void Player::init(float x, float y, float w, float h, World* world, sf::RenderWindow* window) {
	Entity::init(x, y, w, h, world);

	input->init(window);
	input->setSchemes({ Input::InputScheme::WASD, Input::InputScheme::ArrowKeys });

	phys->init(world);
	phys->setKinematic(false);
	phys->setLayer(Physics::Layer::Player);
}

void Player::update() {
	Entity::update();

	control(input->getAxes(), input->getJump(), input->getAttack(), input->getSpecial());
}

void Player::control(sf::Vector2f inputAxes, bool jumping, bool attacking, bool specialing) {
	phys->addForce(sf::Vector2f(inputAxes.x * movementForce, 0));

	jumpCooldownTimer -= world->getTimeScale();
	if (jumping && jumpCooldownTimer <= 0) { // TODO: && touching ground
		// jump!
		phys->addForce(sf::Vector2f(0, -jumpForce));
		jumpCooldownTimer = jumpCooldown;
	}
}
