#include "Entity.h"

Entity::Entity(Rectangle newRect) : rect(newRect)
{
}

Rectangle& Entity::getRect() {
    return rect;
}

std::ostream& operator<<(std::ostream& os, const Entity& entity) {
    os << entity.rect;
    return os;
}
