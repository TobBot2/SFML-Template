#include "Physics.h"

Physics::Physics() {
	init(nullptr);
}
Physics::Physics(Entity* parent) {
	this->parent = parent;
	init(nullptr);
}
void Physics::init(World* world) {
	this->world = world;
	
	kinematic = false;
	friction = .95f;
	bounciness = 1.f;

	mass = 1.f;
	collider = sf::FloatRect(parent->getSprite()->getPosition(), parent->getSprite()->getSize());
	collideMask = ~0; // collide with all by default
	layer = Physics::Layer::Default;
}
void Physics::update() {
	if (!kinematic) // gravity (if not kinematic). Don't addForce. It is not dependent on mass
		vel += sf::Vector2f(0, world->getGravity() * world->getTimeScale());
	vel *= friction;

	parent->getSprite()->move(vel * world->getTimeScale());
	collider.left = parent->getSprite()->getPosition().x;
	collider.top = parent->getSprite()->getPosition().y;

	if (kinematic) return;
	for (Entity* e : * world->getEntities()) {
		// if-guards (not self, has physics, is on collision layer, is intersecting)
		if (e == parent) continue;
		Physics* ePhys = e->getComponent<Physics>();
		if ( (collideMask & (1 << layerAsInt(ePhys->getLayer()))) != (1 << layerAsInt(ePhys->getLayer())) ) continue;
		sf::FloatRect intersection;
		if (!collider.intersects(ePhys->getCollider(), intersection)) continue;

		// get signed intersection
		if (collider.left > ePhys->getCollider().left) { intersection.width *= -1; }
		if (collider.top > ePhys->getCollider().top) { intersection.height *= -1; }

		sf::Vector2f force;
		if (ePhys->getKinematic()) { // KINEMATIC ePhys ---------------
			if (abs(intersection.width) > abs(intersection.height)) { // bounce Y
				parent->getSprite()->move(0, -intersection.height);
				force.y = -vel.y * bounciness * ePhys->getBounciness();
			}
			else { // bounce X
				parent->getSprite()->move(-intersection.width, 0);
				force.x = -vel.x * bounciness * ePhys->getBounciness();
			}
			addForce(force);
		}
		else { // NOT kinematic ePhys ---------------------------------
			if (abs(intersection.width) > abs(intersection.height)) { // bounce Y
				parent->getSprite()->move(0, -intersection.height / 2.f);
				ePhys->parent->getSprite()->move(0, intersection.height / 2.f);
				force.y = -(vel.y - ePhys->getVel().y) * bounciness * ePhys->getBounciness();
			}
			else { // bounce X
				parent->getSprite()->move(-intersection.width / 2.f, 0);
				ePhys->parent->getSprite()->move(intersection.width / 2.f, 0);
				force.x = -(vel.x - ePhys->getVel().x) * bounciness * ePhys->getBounciness();
			}
			addForce(force / 2.f);
			ePhys->addForce(-force / 2.f);
		}
	}
}

void Physics::addForce(sf::Vector2f force) {
	vel += force / mass * world->getTimeScale();
}

void Physics::setCollisionMask(std::vector<Layer> layers) {
	collideMask = 0;
	for (int i = layers.size() - 1; i >= 0; i--) {
		collideMask = collideMask | (1 << layerAsInt(layers[i]));
	}
}

// offsets extruding outward from sprite edges
void Physics::setCollider(float left, float right, float top, float bottom) {
	sf::Vector2u size = parent->getSprite()->getTexture()->getSize();
	collider.width = size.x + left + right;
	collider.height = size.y + top + bottom;
}
sf::FloatRect Physics::getCollider() { return collider; }

void Physics::setKinematic(bool kine) { kinematic = kine; }
bool Physics::getKinematic() { return kinematic; }

void Physics::setLayer(Layer newLayer) { layer = newLayer; }
Physics::Layer Physics::getLayer() { return layer; }

void Physics::setBounciness(float bounce) { bounciness = bounce; }
float Physics::getBounciness() { return bounciness; }

void Physics::setFriction(float friction) { this->friction = friction; }

sf::Vector2f Physics::getVel() { return vel; }

int Physics::layerAsInt(Layer const value) {
	return static_cast<int>(value);
}