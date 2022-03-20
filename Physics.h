#pragma once
#include "Component.h"
#include "World.h"

#include <SFML/System.hpp>
class Physics : public Component {
public:
	enum class Layer
	{
		Default,
		Player,
		Wall,
		Enemy,
		Pickup,
	};
	Physics();
	Physics(Entity* parent);
	void init(World* world);
	void update();
	void addForce(sf::Vector2f force);

	void setCollisionMask(std::vector<Layer> layers);

	void setCollider(float left, float right, float top, float bottom);
	sf::FloatRect getCollider();
	void setKinematic(bool kine);
	bool getKinematic();
	void setLayer(Layer newLayer);
	Layer getLayer();
	void setBounciness(float bounce);
	float getBounciness();
	void setFriction(float friction);

	sf::Vector2f getVel();

private:
	World* world;

	bool kinematic;
	float friction;
	float bounciness;

	float mass;

	sf::FloatRect collider;

	sf::Vector2f vel;

	int collideMask;
	Layer layer;

	int layerAsInt(Layer const layer);
};