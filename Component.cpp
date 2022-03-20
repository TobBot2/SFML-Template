#include "Component.h"
#include "Entity.h"

Component::Component() { parent = nullptr; }
Component::Component(Entity* parent) {
	this->parent = parent;
}
void Component::setParent(Entity* parent) {
	this->parent = parent;
}

void Component::update() { }
