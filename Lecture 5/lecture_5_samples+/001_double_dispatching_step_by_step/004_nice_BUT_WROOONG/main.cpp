#include <iostream>
using namespace std;

#include "AbstractCollider.h"
#include "AABBCollider.h"
#include "SphereCollider.h"

int main (void) {
    //Looking at the implementation of collides(AbstractCollider*) in the AABBCollider and SphereCollider subclasses,
    //we can see they are exactly the same. That might lead you to believe you might be able to move this method into
    //their common subclass. You'd be wrong however as this sample show.
    //Also see AbstractCollider.cpp
    AbstractCollider* aabb = new AABBCollider();
    AbstractCollider* sphere = new SphereCollider();

    aabb->collides(aabb);
    aabb->collides(sphere);
    sphere->collides(aabb);
    sphere->collides(sphere);

    return 0;
}
