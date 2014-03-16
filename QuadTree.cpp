#include "QuadTree.h"

//for level order traversal only
#include <queue>

/*
 * For debugging
 * Visit the one you are currently on and then visit its children
 * Uses tabs to show which level you are on
 */
void QuadTree::preOrderTraversal() {
    for (int i = 0; i < level; i++) {
        std::cout << "\t";
    }
    std::cout << "Entity count: " << entities.size() << "\n";
    for (int i = 0; i < level; i++) {
        std::cout << "\t";
    }
    std::cout << "Bounds: " << boundingBox << "\n";
    for (auto& i : nodes) {
        i->preOrderTraversal();
    }
}

/*
 * Not really helpful in debugging but it shows how postorder traversal works
 * traverse all the nodes down as far as possible
 * visit it
 */
void QuadTree::postOrderTraversal() {
    for (auto& i : nodes) {
        i->postOrderTraversal();
    }
    for (int i = 0; i < level; i++) {
        std::cout << "\t";
    }
    std::cout << "Entity count: " << entities.size() << "\n";
}

/*
 * For debugging
 * Create a queue of QuadTree*
 * push the one you are in onto the queue
 * while there is something in the queue
 *   get the first one off the queue
 *   visit it
 *   push the children of it onto the queue
 */
void QuadTree::levelOrderTraversal() {
    std::queue<QuadTree*> levelOrder;
    levelOrder.push(this);
    QuadTree* current = nullptr;
    while (!levelOrder.empty()) {
        current = levelOrder.front();
        levelOrder.pop();
        for (int i = 0; i < current->level; i++) {
            std::cout << "\t";
        }
        std::cout << "Entity count: " << current->entities.size() << "\n";
        for (auto& i : current->nodes) {
            levelOrder.push(i);
        }
    }
}

QuadTree::QuadTree(int newLevel, Rectangle rect)
         : level(newLevel), boundingBox(rect) {
}

QuadTree::~QuadTree() {
    clear();
}

void QuadTree::clear() {
    entities.clear();
    for (auto i : nodes) {
        i->clear();
        delete i;
        i = nullptr;
    }
    nodes.clear();
}

void QuadTree::insert(Entity* entity) {
    if (hasChildren()) {
        int index = getIndex(entity->getRect());
        if (index != NO_QUADRANT) {
            nodes[index]->insert(entity);
            return;
        }
    }
    entities.push_back(entity);
    if (entities.size() > MAX_ENTITIES && level < MAX_LEVELS) {
        if (!hasChildren()) {
            split();
        }
        unsigned i = 0;
        int index;
        while (i < entities.size()) {
            index = getIndex(entities.at(i)->getRect());
            if (index != -1) {
                Entity* currentEntity = entities.at(i);
                entities.erase(entities.begin() + i);
                nodes[index]->insert(currentEntity);
            } else {
                i++;
            }
        }
    }
}

/*
 * Sets up for retrieving the possible collisions
 */
std::vector<Entity*> QuadTree::retrievePossibleCollisions(Entity* entity) {
    std::vector<Entity*> possibleCollisions;
    return retrieve(possibleCollisions, entity);
}

/*
 * gets the quadrant the entity is in
 * if it is in a quadrant and the node you are in has children
 *   recurse on the nodes index retrieve
 * else
 *   populate the returning list and return it
 */
std::vector<Entity*>& QuadTree::retrieve(std::vector<Entity*>& returnEntities,
                                         Entity* entity) {
    int index = getIndex(entity->getRect());
    if (index != NO_QUADRANT && hasChildren()) {
        nodes[index]->retrieve(returnEntities, entity);
    }
    for (auto& i : entities) {
        returnEntities.push_back(i);
    }
    return returnEntities;
}

bool QuadTree::hasChildren() {
    return nodes.size() > 0;
}

/*
 *    II  |  I
 *    ---------
 *    III | IV
 *
 * Splits into 4 quadrants with half the size
 */
void QuadTree::split() {
    Vec2f subSize = {boundingBox.getWidth() / 2, boundingBox.getHeight() / 2};
    Vec2f position = boundingBox.getPosition();
    nodes.push_back(new QuadTree(level+1, Rectangle(position.x + subSize.x, position.y, subSize)));
    nodes.push_back(new QuadTree(level+1, Rectangle(position, subSize)));
    nodes.push_back(new QuadTree(level+1, Rectangle(position.x, position.y + subSize.y, subSize)));
    nodes.push_back(new QuadTree(level+1, Rectangle(position.x + subSize.x, position.y + subSize.y, subSize)));
}

/*
 * Determines which quadrant the rectangle is in
 * Checks the bounds of each sub quadrant
 */
int QuadTree::getIndex(Rectangle& rect) {
    int index = NO_QUADRANT;
    Vec2f midPoint = boundingBox.getCenter();
    // Top quadrants
    bool topQuadrant = rect.getPosition().y + rect.getHeight() < midPoint.y;
    // Bottom quadrants
    bool bottomQuadrant = rect.getPosition().y > midPoint.y;

    // Left quadrants
    if (rect.getPosition().x + rect.getWidth() < midPoint.x) {
        if (topQuadrant) {
            index = QUADRANT_2;
        } else if (bottomQuadrant) {
            index = QUADRANT_3;
        }
    }
    // Right quadrants
    else if (rect.getPosition().x > midPoint.x) {
        if (topQuadrant) {
            index = QUADRANT_1;
        } else if (bottomQuadrant) {
            index = QUADRANT_4;
        }
    }
    return index;
}
