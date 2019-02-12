#ifndef ABSTRACTCOLLIDER_H
#define ABSTRACTCOLLIDER_H

class AABBCollider;
class SphereCollider;


class AbstractCollider
{
    public:
        AbstractCollider();
        virtual ~AbstractCollider();

        virtual bool collides(AbstractCollider* pParam);
        virtual bool collides(SphereCollider* pParam) = 0;
        virtual bool collides(AABBCollider* pParam) = 0;
};

#endif // ABSTRACTCOLLIDER_H
