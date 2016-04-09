#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "Object.h"

class DynamicObject : public Object
{
public:
	DynamicObject(b2World& world, b2BodyDef &bDef, b2FixtureDef &fDef, const sf::Texture &text);
};
#endif // DYNAMIC_OBJECT_H

DynamicObject::DynamicObject(b2World& world, b2BodyDef &bDef, b2FixtureDef &fDef, const sf::Texture &text)
{
	active = false;
	done = false;
	isForceActive = false;
	bDef.type = b2_dynamicBody;
	body = world.CreateBody(&bDef);
	body->CreateFixture(&fDef);
	sprite = new sf::Sprite(text);
	sprite->setOrigin(sprite->getLocalBounds().width / 2.f, sprite->getLocalBounds().height / 2.f);
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
}


