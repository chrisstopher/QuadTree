#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, float w, float h)
    : position(x, y), size(w, h) {
}

Rectangle::Rectangle(float x, float y, Vec2f& newSize) : position(x, y) {
    setSize(newSize);
}

Rectangle::Rectangle(Vec2f& newPosition, float w, float h) : size(w, h) {
    setPosition(newPosition);
}

Rectangle::Rectangle(Vec2f& newPosition, Vec2f& newSize) {
    setPosition(newPosition);
    setSize(newSize);
}

Rectangle::~Rectangle() {

}

void Rectangle::setPosition(Vec2f& newPosition) {
    position = newPosition;
}

void Rectangle::setSize(Vec2f& newSize) {
    size = newSize;
}

Vec2f& Rectangle::getPosition() {
    return position;
}

float Rectangle::getWidth() const {
    return size.x;
}

float Rectangle::getHeight() const {
    return size.y;
}

Vec2f Rectangle::getCenter() {
    return {position.x + getWidth() / 2,
            position.y + getHeight() / 2};
}

float Rectangle::area() {
    return getWidth() * getHeight();
}

bool Rectangle::collided(Rectangle& rectangle) {
    return (position.x + getWidth()) > rectangle.getPosition().x &&
            position.x < (rectangle.getPosition().x + rectangle.getWidth()) &&
            (position.y + getHeight()) > rectangle.getPosition().y &&
            position.y < (rectangle.getPosition().y + rectangle.getHeight());
}

bool Rectangle::isFullyInside(Rectangle rectangle) {
    return rectangle.getPosition().x <= getPosition().x &&
           (rectangle.getPosition().x + rectangle.getWidth()) >= (getPosition().x + getWidth()) &&
            rectangle.getPosition().y <= getPosition().y &&
            (rectangle.getPosition().y + rectangle.getHeight()) >= (getPosition().y + getHeight());
}

std::ostream& operator<<(std::ostream& os, Rectangle& rectangle) {
    os << rectangle.getPosition().x << ", "
       << rectangle.getPosition().y << " "
       << rectangle.getWidth() << ", "
       << rectangle.getHeight();
    return os;
}
