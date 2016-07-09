#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H
#include "Object.h"

class StaticObject : public Object {
public:
	StaticObject(b2World& world, sf::RenderWindow *window, objTemplate &cOptions) : Object() {
		cOptions.fixtDef.shape = &cOptions.b2Shape; // set fixture shape to b2shape address
		switch (cOptions.sfShape)
		{
		case Shape::square:
			cOptions.dimension.y = cOptions.dimension.x;
			cOptions.b2Shape.SetAsBox((cOptions.dimension.x) / SCALE, (cOptions.dimension.y) / SCALE);
			shape = new sf::CircleShape(roundf((float)sqrt(pow(cOptions.dimension.x, 2) * 2)), 4);
			break;
		default:
			std::cout << "ERROR: No Shape Matches Input!\n";
			break;
		}

		shape->setOrigin(shape->getLocalBounds().width / 2.f, shape->getLocalBounds().height / 2.f);
		shape->setFillColor(cOptions.color);
		shape->setOutlineThickness(0 - cOptions.dimension.x / 4);
		shape->setOutlineColor(sf::Color::Black);

		cOptions.bodyDef.type = b2_staticBody;
		body = world.CreateBody(&cOptions.bodyDef);
		body->CreateFixture(&cOptions.fixtDef);

	}
}; 
#endif // STATIC_OBJECT_