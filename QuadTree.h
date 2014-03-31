#ifndef QUADTREE_H
#define QUADTREE_H

#include "Entity.h"
#include "Rectangle.h"
#include <vector>
#include <memory>

class QuadTree {
    public:
        QuadTree(int newLevel, Rectangle rect);
        ~QuadTree();
        QuadTree(const QuadTree& qTree) = delete;               //TO DO
        QuadTree(QuadTree&& qTree) = delete;                    //TO DO
        QuadTree& operator=(const QuadTree& qTree) = delete;    //TO DO
        QuadTree& operator=(QuadTree&& qTree) = delete;         //TO DO
        void clear();
        void insert(const std::shared_ptr<Entity>& entity);
        std::vector<std::weak_ptr<Entity>> retrievePossibleCollisions(std::shared_ptr<Entity>& entity);
        //For testing only
        void preOrderTraversal();
    private:
        int level;
        enum {
            NO_QUADRANT = -1,
            QUADRANT_1,
            QUADRANT_2,
            QUADRANT_3,
            QUADRANT_4,
            //Easily changeable max number of levels and entities per quadrant
            MAX_LEVELS = 5,
            MAX_ENTITIES = 8
        };
        std::vector<std::shared_ptr<QuadTree>> nodes;
        std::vector<std::weak_ptr<Entity>> entities;
        Rectangle boundingBox;
        std::vector<std::weak_ptr<Entity>>& retrieve(std::vector<std::weak_ptr<Entity>>& entities,
                                                     const std::weak_ptr<Entity>& entity);
        bool hasChildren();
        void split();
        int getIndex(Rectangle& rect);
};


#endif // QUADTREE_H
