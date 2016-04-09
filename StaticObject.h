#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "Object.h"


class StaticObject : public Object
{
public:
	StaticObject(b2World& world, b2BodyDef &bDef, b2FixtureDef &fDef, const sf::Texture &text);
};
#endif // STATIC_OBJECT_H

StaticObject::StaticObject(b2World& world, b2BodyDef &bDef, b2FixtureDef &fDef, const sf::Texture &text)
{
	active = false;
	done = false;
	isForceActive = false;
	bDef.type = b2_staticBody;
	body = world.CreateBody(&bDef);
	body->CreateFixture(&fDef);
	sprite = new sf::Sprite(text);
	sprite->setOrigin(sprite->getLocalBounds().width / 2.f, sprite->getLocalBounds().height / 2.f);
	r = g = b = 255;
	
}
