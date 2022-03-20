#include "World.h"

World::World() {
	gravity = 100.f;

	dt = 1.f / 60;
	timescale = 1.f;

	paused = false;
}

float World::getTimeScale() { return dt * timescale; }

std::vector<Entity*>* World::getEntities() {
	return &entities;
}

float World::getGravity() { return gravity; }
void World::setGravity(float force) { gravity = force; }

void World::removeEntity(int index) {
	delete entities[index];
	entities.erase(entities.begin() + index);
}

void World::update(float deltaTime) {
	dt = deltaTime;

	if (!paused) {
		for (Entity* e : entities) {
			e->update();
		}
	}
}
void World::render(sf::RenderWindow* window) {
	for (Entity* e : entities) {
		window->draw(* e->getSprite());
	}
}
