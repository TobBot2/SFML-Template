#pragma once
#include "Entity.h"
#include "Input.h"
#include "Physics.h"

class Player : public Entity {
public:
	Player();
	virtual void init(float x, float y, float w, float h, World* world, sf::RenderWindow* window);
	virtual void update();

	void control(sf::Vector2f inputAxes, bool jumping, bool attacking, bool specialing);

private:
	Physics* phys;
	Input* input;

	float jumpForce;
	float jumpCooldownTimer;
	const float jumpCooldown = 2.f;

	float movementForce;
};