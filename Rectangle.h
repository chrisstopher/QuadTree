#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vec2f.h"
#include <iostream>

class Rectangle {
    public:
        Rectangle(float x, float y, float w, float h);
        Rectangle(float x, float y, Vec2f& newSize);
        Rectangle(Vec2f& newPosition, float w, float h);
        Rectangle(Vec2f& newPosition, Vec2f& newSize);
        virtual ~Rectangle();

        void setPosition(Vec2f& newPosition);
        void setSize(Vec2f& newSize);

        Vec2f& getPosition();
        float getWidth() const;
        float getHeight() const;
        Vec2f getCenter();

        float area();
        bool collided(Rectangle& rectangle);
        bool isFullyInside(Rectangle rectangle);

        friend std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle);
    protected:
        Vec2f position, size;
};



#endif // RECTANGLE_H

