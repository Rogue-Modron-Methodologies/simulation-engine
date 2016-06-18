#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H
#include "Object.h"

class StaticObject : public Object {
public:
	StaticObject(b2World& world, b2BodyDef &bDef, b2FixtureDef &fDef) : Object() {
	bDef.type = b2_staticBody;
	body = world.CreateBody(&bDef);
	body->CreateFixture(&fDef);	
	shape = new sf::CircleShape(20.0, 4);
	shape->setOrigin(shape->getLocalBounds().width / 2.f, shape->getLocalBounds().height / 2.f);
	}
}; 
#endif // STATIC_OBJECT_