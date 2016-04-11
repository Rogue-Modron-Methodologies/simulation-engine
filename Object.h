#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include <iostream>

// pixel to real-world conversion
static const float SCALE = 30.f;

class Object
{
protected:
	b2Body* body;
	sf::Sprite* sprite;
	bool isForceActive;
	b2Vec2 activeForce;
	int forceDuration;
	int r, g, b;
	bool active;
	bool done;

public:
	virtual void update(); 
	virtual void draw(sf::RenderWindow &window);
	void applyForce(b2Vec2 force, int duration);	
	bool isTargeted(sf::RenderWindow &window);
	void destroy(b2World& world);

private:
	sf::Vector2f convertCoord(sf::RenderWindow &window);

};
#endif // OBJECT_H
