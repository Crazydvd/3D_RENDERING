#include <iostream>
using namespace std;

#include "AbstractCollider.h"
#include "AABBCollider.h"
#include "SphereCollider.h"

int main (void) {
    //this is what we would like to implement
    //but it isn't working since all colliders only have
    //isColliding (AABBCollider) & isColliding (SphereCollider) in their interface
    //and C++ doesn't know how to match AbstractCollider with either of them since
    //overloading is a compile time feature, unlike overriding which is a runtime feature!!

    AbstractCollider* aabb = new AABBCollider();
    AbstractCollider* sphere = new SphereCollider();

    aabb->collides(aabb);
    aabb->collides(sphere);
    sphere->collides(aabb);
    sphere->collides(sphere);

    return 0;
}
