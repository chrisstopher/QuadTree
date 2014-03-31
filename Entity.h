#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Rectangle.h"

class Entity
{
public:
    explicit Entity(Rectangle newRect);
    Rectangle& getRect();
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity);
private:
    Rectangle rect;
};



#endif // ENTITY_H
