#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "3d_rendering_asign_3/config.hpp"
#include "3d_rendering_asign_3/assignment3.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
Assignment3::Assignment3() :AbstractGame(), _hud(0)
{

}

void Assignment3::initialize()
{
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void Assignment3::_initializeScene()
{
	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* planeMeshDefault = Mesh::load(config::ASSIGNMENT3_MODEL_PATH + "plane.obj");
	Mesh* cubeMeshF = Mesh::load(config::ASSIGNMENT3_MODEL_PATH + "cube_flat.obj");
	Mesh* sphereMeshS = Mesh::load(config::ASSIGNMENT3_MODEL_PATH + "sphere_smooth.obj");
	Mesh* SuzannaS = Mesh::load(config::ASSIGNMENT3_MODEL_PATH + "suzanna_smooth.obj");
	Mesh* TeapotS = Mesh::load(config::ASSIGNMENT3_MODEL_PATH + "teapot_smooth.obj");
	Mesh* TeapotF = Mesh::load(config::ASSIGNMENT3_MODEL_PATH + "teapot_flat.obj");

	//MATERIALS

	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
	AbstractMaterial* litMaterial = new LitMaterial(glm::vec3(0, 0.5f, 0), glm::vec3(1, 1, 1));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::ASSIGNMENT3_TEXTURE_PATH + "runicfloor.png"));
	AbstractMaterial* brickMaterial = new TextureMaterial(Texture::load(config::ASSIGNMENT3_TEXTURE_PATH + "bricks.jpg"));
	AbstractMaterial* landMaterial = new TextureMaterial(Texture::load(config::ASSIGNMENT3_TEXTURE_PATH + "land.jpg"));

	//SCENE SETUP

   //add camera first (it will be updated last)
	Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	//add the floor
	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(5, 5, 5));
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(new LitMaterial(glm::vec3(0.5,0,0), glm::vec3(0.5,0,0)));
	_world->add(plane);

	////add a spinning sphere
	//GameObject* sphere = new GameObject ("sphere", glm::vec3(0,0,0));
	//sphere->scale(glm::vec3(2.5,2.5,2.5));
	//sphere->setMesh (sphereMeshS);
	//sphere->setMaterial(runicStoneMaterial);
	//sphere->setBehaviour (new RotatingBehaviour());
	//_world->add(sphere);

	//add a teapot
	GameObject* teapot = new GameObject("teapot", glm::vec3(0, 1, 0));
	teapot->scale(glm::vec3(2.5, 2.5, 2.5));
	teapot->setMesh(TeapotS);
	teapot->setMaterial(litMaterial);
	teapot->setTransform(glm::rotate(teapot->getWorldTransform(), glm::radians(75.0f), glm::vec3(0, 1, 0)));
	teapot->setTransform(glm::rotate(teapot->getWorldTransform(), glm::radians(-10.0f), glm::vec3(1, 0, 0)));
	//teapot->setBehaviour (new RotatingBehaviour());
	_world->add(teapot);

	//add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
	//It's here as a place holder to get you started.
	//Note how the texture material is able to detect the number of lights in the scene
	//even though it doesn't implement any lighting yet!

	glm::vec3 color = glm::vec3(1, 1, 1);
	lightMaterial = new ColorMaterial(color);

	Light* light = new Light("light", glm::vec3(0, 4, 0), LightType::POINT);
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->setMesh(cubeMeshF);
	light->setMaterial(lightMaterial);
	light->setBehaviour(new KeysBehaviour(25,90));
	_world->add(light);

	light->setAmbientContribution(.5f);
	light->SetLightIntensity(1);
	light->SetLightColor(color);

	LitMaterial::Light = light;
}

void Assignment3::_render()
{
	AbstractGame::_render();
	_updateHud();
}

void Assignment3::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

Assignment3::~Assignment3()
{
	//dtor
}
