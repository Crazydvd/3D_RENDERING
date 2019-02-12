#include "SphereCollider.h"
#include <iostream>
using namespace std;

SphereCollider::SphereCollider()
{
    //ctor
}

SphereCollider::~SphereCollider()
{
    //dtor
}

bool SphereCollider::collides(AbstractCollider* pParam) {
    cout << "SphereCollider.collides (AbstractCollider)" << endl;
    return false;
}

bool SphereCollider::collides(AABBCollider* pParam) {
    cout << "SphereCollider.collides (AABBCollider)" << endl;
    return false;
}

bool SphereCollider::collides(SphereCollider* pParam) {
    cout << "SphereCollider.collides (SphereCollider)" << endl;
    return false;
}

