#include "Entity.h"

Entity::Entity(Rectangle newRect) : rect(newRect)
{
}

Rectangle& Entity::getRect() {
    return rect;
}

std::ostream& operator<<(std::ostream& os, Entity* entity) {
    os << entity->getRect();
    return os;
}
