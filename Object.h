#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>

enum class Shape { circle, rectangle, square, triangle };

// pixel to real-world conversion
static const float SCALE = 30.f;

struct objTemplate {
	b2PolygonShape b2Shape;
	b2BodyDef bodyDef;
	b2FixtureDef fixtDef;   // density, friction, shape, restitution
	int quantity;
	b2Vec2 dimension;
	b2Vec2 position;
	Shape sfShape;
	sf::Color color;
	//shape.setOutlineThickness(10);
	//shape.setOutlineColor(sf::Color(250, 150, 100));
};

// force structure/class
// b2Vec2 force
// double duration
// bool active
// updateForces()

class Object { //: public sf::Drawable, public sf::Transformable
protected:
	b2Body* body;
	sf::Shape *shape;
	bool isForceActive;
	b2Vec2 activeForce;
	int forceDuration;
	bool active;
	bool done;

public:
	Object() {
		active = false;
		done = false;
		isForceActive = false;		
	}
	virtual void update(); 
	virtual void draw(sf::RenderWindow &window);
	void applyForce(b2Vec2 force, int duration);	
	bool isTargeted(sf::RenderWindow &window);
	void destroy(b2World& world);
	static sf::Color randColor() { return sf::Color(rand() % 255, rand() % 255, rand() % 255); }
private:
	sf::Vector2f convertCoord(sf::RenderWindow &window);
};
#endif // OBJECT_H