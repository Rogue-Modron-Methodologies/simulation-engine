#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>

enum class Shape { square, circle, triangle };

// pixel to real-world conversion
static const float SCALE = 30.f;

// force structure/class
// b2Vec2 force
// double duration
// bool active
// updateForces()

class Object //: public sf::Drawable, public sf::Transformable
{
protected:
	b2Body* body;
	//sf::Drawable *sprite;   // zzzz dynamic casting
	sf::Shape *shape;
	//sf::Sprite* sprite;
	bool isForceActive;
	b2Vec2 activeForce;
	int forceDuration;
	bool active;
	bool done;

public:
	Object(const sf::Texture &text)
	{
		active = false;
		done = false;
		isForceActive = false;
		
	}
	virtual void update(); 
	virtual void draw(sf::RenderWindow &window);
	void applyForce(b2Vec2 force, int duration);	
	bool isTargeted(sf::RenderWindow &window);
	void destroy(b2World& world);
	void setColor(sf::Color c = sf::Color::Transparent) { shape->setFillColor(c); }
	static sf::Color randColor() { return sf::Color(rand() % 255, rand() % 255, rand() % 255); }

private:
	sf::Vector2f convertCoord(sf::RenderWindow &window);

};
#endif // OBJECT_H