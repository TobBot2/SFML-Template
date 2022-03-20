#pragma once
#include "classes.h"
#include "Entity.h"

class Component {
public:
	Component();
	Component(Entity* parent);
	void setParent(Entity* parent);
	virtual void update();
protected:
	Entity* parent;
};