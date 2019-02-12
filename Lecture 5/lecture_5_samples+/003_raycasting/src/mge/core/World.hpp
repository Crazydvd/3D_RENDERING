#ifndef WORLD_HPP
#define WORLD_HPP

#include "mge/core/GameObject.hpp"

class Camera;

class World : public GameObject
{
	public:
        World();

		void setMainCamera (Camera* pCamera);
		Camera* getMainCamera();

	private:
	    Camera* _mainCamera;

        World(const World&);
        World& operator=(const World&);
};


#endif // WORLD_HPP
