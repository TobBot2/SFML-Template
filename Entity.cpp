#include "Entity.h"

Entity::Entity() {
	world = nullptr;

	sprite.setSize(sf::Vector2f(32, 32));
}
Entity::~Entity() {
	while (components.size() != 0) {
		delete components[0];
		components.erase(components.begin());
	}
}

void Entity::init(float x, float y, float w, float h, World* world)
{
	sprite.setPosition(x, y);
	sprite.setSize(sf::Vector2f(w, h));
	sprite.setFillColor(sf::Color::White);

	this->world = world;
}

void Entity::update() {
	for (auto c : components) {
		c->update();
	}
}

sf::RectangleShape* Entity::getSprite() {
	return &sprite;
}

