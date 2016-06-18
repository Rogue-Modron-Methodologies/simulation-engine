#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "Object.h"

class DynamicObject : public Object
{
public:
	DynamicObject(b2World& world, sf::RenderWindow *window, Options &cOptions) : Object()
	{
		cOptions.b2Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
		cOptions.fixtDef.shape = &cOptions.b2Shape;
		cOptions.bodyDef.position = b2Vec2(rand() % window->getSize().x / SCALE, rand() % window->getSize().y / SCALE);
		cOptions.bodyDef.type = b2_dynamicBody;
		body = world.CreateBody(&cOptions.bodyDef);
		body->CreateFixture(&cOptions.fixtDef);

		shape = new sf::CircleShape(roundf((float)sqrt(pow(16.0, 2) * 2)), 4); 
		shape->setOrigin(shape->getLocalBounds().width / 2.f, shape->getLocalBounds().height / 2.f);
		shape->setFillColor(cOptions.color);
		shape->setOutlineThickness(-3);
		shape->setOutlineColor(sf::Color::Black);
	}
};
#endif // DYNAMIC_OBJECT_H





