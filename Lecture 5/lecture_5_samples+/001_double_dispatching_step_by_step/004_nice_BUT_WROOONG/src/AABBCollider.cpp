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

bool AABBCollider::collides(AABBCollider* pParam) {
    cout << "AABBCollider.collides (AABBCollider)" << endl;
    return false;
}

bool AABBCollider::collides(SphereCollider* pParam) {
    cout << "AABBCollider.collides (SphereCollider)" << endl;
    return false;
}
