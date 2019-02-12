#include <iostream>
using namespace std;

#include "AbstractCollider.h"
#include "AABBCollider.h"
#include "SphereCollider.h"

int main (void) {

    //The good news is we can now compile, the bad news is every call default to
    //choosing the overloaded method in the collider class which matches the AbstractCollider* parameter
    //since that is the type we used to declare the variables below...
    AbstractCollider* aabb = new AABBCollider();
    AbstractCollider* sphere = new SphereCollider();

    aabb->collides(aabb);
    aabb->collides(sphere);
    sphere->collides(aabb);
    sphere->collides(sphere);

    return 0;
}
