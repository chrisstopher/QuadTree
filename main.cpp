#include <iostream>
#include <vector>
#include "QuadTree.h"

int main(int argc, char* argv[]) {
    QuadTree qTree(0, Rectangle(0, 0, 600, 600));
    std::vector<Entity*> entities;
    //QUAD 1
    entities.push_back(new Entity(Rectangle(325, 0, 32, 32)));
    entities.push_back(new Entity(Rectangle(325 + 30, 0, 32, 32)));
    entities.push_back(new Entity(Rectangle(325, 28, 32, 32)));
    entities.push_back(new Entity(Rectangle(325 + 100, 50, 32, 32)));
    entities.push_back(new Entity(Rectangle(325 + 100, 100, 32, 32)));
    entities.push_back(new Entity(Rectangle(325 + 100, 200, 32, 32)));

    entities.push_back(new Entity(Rectangle(325 + 200, 50, 32, 32)));
    entities.push_back(new Entity(Rectangle(325 + 200, 100, 32, 32)));
    entities.push_back(new Entity(Rectangle(325 + 200, 200, 32, 32)));

    //this is not in any quadrant
    //for every other entity this shows up in their quadrant which is awsume
    //but when checking this one, this one only shows up which is bad
    //not really bad because your going to have to loop over them all each frame anyway
    //so you will be able to see this on every other entities collision
    entities.push_back(new Entity(Rectangle(290, 290, 32, 32)));

    //QUAD 2
    entities.push_back(new Entity(Rectangle(0, 0, 32, 32)));
    entities.push_back(new Entity(Rectangle(50, 0, 32, 32)));
    entities.push_back(new Entity(Rectangle(0, 100, 32, 32)));

    //QUAD 3
    entities.push_back(new Entity(Rectangle(0, 325, 32, 32)));

    //QUAD 4
    entities.push_back(new Entity(Rectangle(325, 325, 32, 32)));
    entities.push_back(new Entity(Rectangle(325 + 50, 325 + 50, 32, 32)));

    for (auto& i : entities) {
        std::cout << i << "\n";
        qTree.insert(i);
    }
    for (auto& i : entities) {
        auto possibleCollisions = qTree.retrievePossibleCollisions(i);
        std::cout << "\nThere are " << possibleCollisions.size() << " possible collisions for " << i << "\n";
        for (auto& j : possibleCollisions) {
            if (i == j) {//if they are the same entity then do not test anything
                std::cout << "\t" << j << "\n";
                continue;
            }
            if (i->getRect().collided(j->getRect())) {
                std::cout << "\t" << i << " collided with " << j << "\n";
            } else {
                std::cout << "\t" << j << "\n";
            }
        }
    }

    std::cout << "\nPre order traversal:\n";
    qTree.preOrderTraversal();

    //std::cout << "\nLevel order traversal:\n";
    //qTree.levelOrderTraversal();

    //std::cout << "\nPost order traversal:\n";
    //qTree.postOrderTraversal();

    for (auto& i : entities) {
        delete i;
    }
    qTree.clear();
    entities.clear();
    return 0;
}

