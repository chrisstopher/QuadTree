#ifndef QUADTREE_H
#define QUADTREE_H

#include "Entity.h"
#include "Rectangle.h"
#include <vector>

class QuadTree {
    public:
        QuadTree(int newLevel, Rectangle rect);
        void clear();
        void insert(Entity* entity);
        std::vector<Entity*> retrievePossibleCollisions(Entity* entity);
        void preOrderTraversal();
        void postOrderTraversal();
        void levelOrderTraversal();
    private:
        int level;
        enum {
            NO_QUADRANT = -1,
            QUADRANT_1,
            QUADRANT_2,
            QUADRANT_3,
            QUADRANT_4,
            //MAX_NODES = 4,
            MAX_LEVELS = 5,
            MAX_ENTITIES = 8
        };
        std::vector<QuadTree*> nodes;
        std::vector<Entity*> entities;
        Rectangle boundingBox;

        bool hasChildren();
        void split();
        int getIndex(Rectangle& rect);

        std::vector<Entity*>& retrieve(std::vector<Entity*>& entities,
                                       Entity* entity);
};

#endif // QUADTREE_H
