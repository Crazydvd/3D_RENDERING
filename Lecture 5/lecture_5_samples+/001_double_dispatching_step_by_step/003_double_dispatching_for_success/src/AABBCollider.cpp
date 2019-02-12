#include "AABBCollider.h"
#include <iostream>
using namespace std;

AABBCollider::AABBCollider()
{
    //ctor
}

AABBCollider::~AABBCollider()
{
    //dtor
}

bool AABBCollider::collides(AbstractCollider* pParam) {
    cout << "Redispatching..." << endl;
    //by reversing the call in combination with the fact that c++ knows "this" is of concrete type AABBCollider
    //the target is able to choose the correct overloaded method. Ain't that pretty.
    return pParam->collides(this);
}

bool AABBCollider::collides(AABBCollider* pParam) {
    cout << "AABBCollider.collides (AABBCollider)" << endl;
    return false;
}

bool AABBCollider::collides(SphereCollider* pParam) {
    cout << "AABBCollider.collides (SphereCollider)" << endl;
    return false;
}
