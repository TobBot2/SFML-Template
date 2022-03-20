#pragma once
#include "classes.h"
#include "Component.h"
#include "World.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Entity {
public:
	Entity();
	~Entity();
	virtual void init(float x, float y, float w, float h, World* world);

	virtual void update();

	sf::RectangleShape* getSprite();
	template<typename T> T* addComponent();
	template<typename T> T* getComponent();

protected:
	World* world;

	sf::RectangleShape sprite;
	std::vector<Component*> components;

};


// dunno why these have to be in the header
template<typename T>
inline T* Entity::addComponent() {
	T* c = new T(this);
	components.push_back(c);
	return c;
}

template<typename T>
inline T* Entity::getComponent() {
	for (Component* c : components) {
		T* t = dynamic_cast<T*>(c);
		if (t != nullptr) {
			return t;
		}
	}
	return nullptr;
}