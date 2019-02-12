#ifndef AABBCOLLIDER_H
#define AABBCOLLIDER_H

#include <AbstractCollider.h>

class AABBCollider : public AbstractCollider
{
    public:
        AABBCollider();
        virtual ~AABBCollider();

        bool collides(AbstractCollider* pParam);
        bool collides(AABBCollider* pParam);
        bool collides(SphereCollider* pParam);
};

#endif // AABBCOLLIDER_H
