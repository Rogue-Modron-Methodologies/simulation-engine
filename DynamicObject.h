#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "Object.h"

class DynamicObject : public Object
{
public:
	DynamicObject(b2World& world, b2BodyDef &bDef, b2FixtureDef &fDef, const sf::Texture &text) : Object(text)
	{
		bDef.type = b2_dynamicBody;
		body = world.CreateBody(&bDef);
		body->CreateFixture(&fDef);

	}
};
#endif // DYNAMIC_OBJECT_H





