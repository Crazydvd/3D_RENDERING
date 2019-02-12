#include "AbstractCollider.h"
#include "AABBCollider.h"
#include "SphereCollider.h"
#include <iostream>
using namespace std;

AbstractCollider::AbstractCollider()
{
    //ctor
}

AbstractCollider::~AbstractCollider()
{
    //dtor
}

//By moving this method from the subclass into the superclass we introduced an endless loop.
//Why? Because even though we reverse the call, our "this" parameter can only be matched with AbstractCollider
//which means it will call this method over and over again. So... close but no cigar.
bool AbstractCollider::collides(AbstractCollider* pParam) {
    cout << "Redispatching..." << endl;
    return pParam->collides(this);
}
