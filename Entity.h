#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Rectangle.h"

class Entity
{
public:
    explicit Entity(Rectangle newRect);
    Rectangle& getRect();
private:
    Rectangle& rect;
};

std::ostream& operator<<(std::ostream& os, Entity* entity);

#endif // ENTITY_H
