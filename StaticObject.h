#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "Object.h"

class StaticObject : public Object
{
public:
	StaticObject(b2World& world, b2BodyDef &bDef, b2FixtureDef &fDef, const sf::Texture &text) : Object(text) {

	bDef.type = b2_staticBody;
	body = world.CreateBody(&bDef);
	body->CreateFixture(&fDef);	
}
};
#endif // STATIC_OBJECT_