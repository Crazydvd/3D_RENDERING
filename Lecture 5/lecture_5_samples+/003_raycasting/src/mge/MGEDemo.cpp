#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame (),_hud(0), _normalMaterial(0), _hitMaterial(0)
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    //add camera first (it will be updated last)
    Camera* camera = new Camera ("camera", glm::vec3(0,0,0));
    camera->setBehaviour(new KeysBehaviour(5,45));
    _world->add(camera);
    _world->setMainCamera(camera);

    //MESHES
    Mesh* sphereMesh = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");

    //MATERIALS
    _normalMaterial = new ColorMaterial (glm::vec3(1,1,1));
    _hitMaterial = new ColorMaterial (glm::vec3(1,0,0));

    //SCENE SETUP
    int count = 30;
    for (int i = 0; i < count; i++) {
        GameObject* sphere = new GameObject("sphere" + to_string(i), glm::vec3(cos(i/2.0f) * 5, sin(i/2.0f)*5, -10 - 1*i));
        sphere->setMesh(sphereMesh);
        sphere->setMaterial(_normalMaterial);
        _world->add(sphere);
    }
}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();

    sf::Vector2u windowSize = _window->getSize();
    //first get mouse position, which will be between (0,0) and (windowSize.x, windowSize.y)
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    //but we want the mouse position relative to center of the screen, that is where the camera is pointing
    glm::vec2 mousePosRelativeToScreenCenter = glm::vec2 (
            (float)mousePosition.x - (windowSize.x/2),
            (float)-mousePosition.y + (windowSize.y/2)
    );

    //calculate plane distance
    float verticalFOV = 45.0f;  //taken from Camera.hpp
    float distance = (windowSize.y / 2) / tan (glm::radians(verticalFOV/2.0f));

    glm::vec4 ray = glm::vec4(
        mousePosRelativeToScreenCenter.x,
        mousePosRelativeToScreenCenter.y,
        -distance,
        0
    );

    //see where this ray is actually pointing in the world and normalize it so we can use it for projection
    glm::vec3 rayWorld = glm::vec3(_world->getMainCamera()->getWorldTransform() * ray);
    rayWorld = glm::normalize(rayWorld);

    //fake collision loop in here
    for (int i = 0; i < _world->getChildCount(); i++) {
        GameObject* child = _world->getChildAt(i);
        if (child == _world->getMainCamera()) continue;

        //get the vector from camera to object
        glm::vec3 cameraToSphere (child->getWorldPosition() - _world->getMainCamera()->getWorldPosition());
        //project that vector onto the ray so we have the part of cameraToSphere along the ray
        glm::vec3 parallel = glm::dot (cameraToSphere, rayWorld) * rayWorld;
        //subtract that part from the vector to get the vector parallel to our ray
        glm::vec3 perpendicular = cameraToSphere - parallel;
        //and get its distance
        float distance = glm::length(perpendicular);

        //I know the shere radius is 1, this needs to be replaced with collider radius
        if (distance <= 1) {
            child->setMaterial(_hitMaterial);
        } else {
            child->setMaterial(_normalMaterial);
        }
    }

}

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
