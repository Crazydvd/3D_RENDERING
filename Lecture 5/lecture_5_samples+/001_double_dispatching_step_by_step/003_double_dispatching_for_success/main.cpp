#include <iostream>
using namespace std;

#include "AbstractCollider.h"
#include "AABBCollider.h"
#include "SphereCollider.h"

int main (void) {
    //Success yay.
    //By reversing and redispatching the call (hence the name double dispatching)
    //C++ is able to choose the correct overloaded method and everything works as intended
    //See AABBCollider for example.
    AbstractCollider* aabb = new AABBCollider();
    AbstractCollider* sphere = new SphereCollider();

    aabb->collides(aabb);
    aabb->collides(sphere);
    sphere->collides(aabb);
    sphere->collides(sphere);

    return 0;
}
