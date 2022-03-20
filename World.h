#pragma once
#include "classes.h"
#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <vector>
class World {
public:
	World();

	float getTimeScale();
	std::vector<Entity*>* getEntities();
	float getGravity();
	void setGravity(float force);

	template<typename T> T* addEntity();
	void removeEntity(int index);

	void update(float deltaTime);
	void render(sf::RenderWindow* window);

private:
	std::vector<Entity*> entities;
	float gravity;
	float dt;
	float timescale;

	bool paused;
};

template<typename T>
inline T* World::addEntity() {
	T* e = new T();
	entities.push_back(e);
	return e;
}