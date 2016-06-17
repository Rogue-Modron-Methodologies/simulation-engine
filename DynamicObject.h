#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "Object.h"

class DynamicObject : public Object
{
public:
	DynamicObject(b2World& world, b2BodyDef &bDef, b2FixtureDef &fDef) : Object()
	{
		bDef.type = b2_dynamicBody;
		body = world.CreateBody(&bDef);
		body->CreateFixture(&fDef);
		shape = new sf::CircleShape(roundf((float)sqrt(pow(16.0, 2) * 2)), 4); 
		shape->setOrigin(shape->getLocalBounds().width / 2.f, shape->getLocalBounds().height / 2.f);
		shape->setOutlineThickness(-3);
		shape->setOutlineColor(sf::Color::Black);
	}
};
#endif // DYNAMIC_OBJECT_H





