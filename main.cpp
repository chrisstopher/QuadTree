#include <iostream>
#include <vector>
#include <memory>
#include "QuadTree.h"

int main(int argc, char* argv[]) {
    QuadTree qTree(0, Rectangle(0, 0, 600, 600));
    std::vector<std::shared_ptr<Entity>> entities;
    //QUAD 1
    entities.push_back(std::shared_ptr<Entity>(new Entity({325, 0, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({325 + 30, 0, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({325, 28, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({325 + 100, 50, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({325 + 100, 100, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({325 + 100, 200, 32, 32})));

    entities.push_back(std::shared_ptr<Entity>(new Entity({325 + 200, 50, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({325 + 200, 100, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({325 + 200, 200, 32, 32})));

    //this is not in any quadrant
    //for every other entity this shows up in their quadrant
    //so you will be able to see this on every other entities collision
    entities.push_back(std::shared_ptr<Entity>(new Entity({290, 290, 32, 32})));

    //QUAD 2
    entities.push_back(std::shared_ptr<Entity>(new Entity({0, 0, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({50, 0, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({0, 100, 32, 32})));

    //QUAD 3
    entities.push_back(std::shared_ptr<Entity>(new Entity({0, 325, 32, 32})));

    //QUAD 4
    entities.push_back(std::shared_ptr<Entity>(new Entity({325, 325, 32, 32})));
    entities.push_back(std::shared_ptr<Entity>(new Entity({325 + 50, 325 + 50, 32, 32})));

    for (auto& i : entities) {
        std::cout << *i << "\n";
        qTree.insert(i);
    }
    for (auto& i : entities) {
        auto possibleCollisions = qTree.retrievePossibleCollisions(i);
        std::cout << "\nThere are " << possibleCollisions.size() << " possible collisions for " << *i << "\n";
        for (auto& j : possibleCollisions) {
            auto possibleCollider = j.lock();
            if (i == possibleCollider) {//if they are the same entity then do not test anything
                std::cout << "\t" << *i << " == " << *possibleCollider << " are the same.\n";
                continue;
            }
            if (i->getRect().collided(possibleCollider->getRect())) {
                std::cout << "\t" << *i << " collided with " << *possibleCollider << "\n";
            } else {
                std::cout << "\t" << *possibleCollider << "\n";
            }
        }
    }

    std::cout << "\nPre order traversal:\n";
    qTree.preOrderTraversal();

    entities.clear();
    return 0;
}

