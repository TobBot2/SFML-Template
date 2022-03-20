#include "Wall.h"

Wall::Wall() 
	: Entity::Entity(){
	phys = addComponent<Physics>();
}

void Wall::init(float x, float y, float w, float h, World* world) {
	Entity::init(x, y, w, h, world);

	phys->init(world);
	phys->setKinematic(true);
	phys->setLayer(Physics::Layer::Wall);
}
