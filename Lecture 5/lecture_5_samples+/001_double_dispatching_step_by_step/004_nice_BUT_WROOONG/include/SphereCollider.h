#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include <AbstractCollider.h>

//SEE AABBCollider FOR THE DOCS, EXACTLY THE SAME APPLIES TO SphereCollider

class SphereCollider : public AbstractCollider
{
    public:
        SphereCollider();
        virtual ~SphereCollider();

        bool collides(AABBCollider* pParam);
        bool collides(SphereCollider* pParam);
};

#endif // SPHERECOLLIDER_H
