#pragma once
#include "Entity.h"
#include "Physics.h"

class Wall : public Entity {
public:
	Wall();
	virtual void init(float x, float y, float w, float h, World* world);
private:
	Physics* phys;
};

