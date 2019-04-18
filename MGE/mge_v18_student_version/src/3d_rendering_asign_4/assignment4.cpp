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
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "3d_rendering_asign_4/config.hpp"
#include "3d_rendering_asign_4/assignment4.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
Assignment4::Assignment4() :AbstractGame(), _hud(0)
{

}

void Assignment4::initialize()
{
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void Assignment4::_initializeScene()
{
	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* planeMeshDefault = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "plane.obj");
	Mesh* TerrainMesh = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "plane_8192.obj");
	Mesh* cubeMeshF = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "cube_flat.obj");
	Mesh* sphereMeshS = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "sphere_smooth.obj");
	Mesh* SuzannaS = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "suzanna_smooth.obj");
	Mesh* TeapotS = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "teapot_smooth.obj");
	Mesh* TeapotF = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "teapot_flat.obj");
	Mesh* PliersUp = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "pliersUp.obj");
	Mesh* PliersDown = Mesh::load(config::ASSIGNMENT4_MODEL_PATH + "pliersDown.obj");

	//MATERIALS

	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial;
	AbstractMaterial* litMaterial = new LitMaterial(glm::vec3(0, 0.5f, 0), glm::vec3(1, 1, 1));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::ASSIGNMENT4_TEXTURE_PATH + "runicfloor.png"));
	AbstractMaterial* brickMaterial = new TextureMaterial(Texture::load(config::ASSIGNMENT4_TEXTURE_PATH + "bricks.jpg"));
	AbstractMaterial* landMaterial = new TextureMaterial(Texture::load(config::ASSIGNMENT4_TEXTURE_PATH + "land.jpg"));
	AbstractMaterial* litTexture = new TerrainMaterial(Texture::load(config::ASSIGNMENT4_TEXTURE_PATH + "diffuse4.jpg"));
	AbstractMaterial* terrain = new TerrainMaterial(Texture::load(config::ASSIGNMENT4_TEXTURE_PATH + "heightmap.png"));

	//SCENE SETUP

   //add camera first (it will be updated last)
	Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	//add the floor
	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(5, 5, 5));
	plane->setMesh(TerrainMesh);
	plane->setMaterial(terrain);
	_world->add(plane);

	//add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
	//It's here as a place holder to get you started.
	//Note how the texture material is able to detect the number of lights in the scene
	//even though it doesn't implement any lighting yet!

	glm::vec3 color = glm::vec3(1, 1, 1);
	lightMaterial = new ColorMaterial(color);

	Light* light = new Light("light", glm::vec3(0, 1, 0), LightType::POINT);
	light->translate(glm::vec3(-3, 0, 4));
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->rotate(glm::radians(135.0f), glm::vec3(0, 1, 0));
	light->setMesh(cubeMeshF);
	light->setMaterial(lightMaterial);
	light->setBehaviour(new KeysBehaviour(25, 90));
	_world->add(light);

	//second light
	Light* light2 = new Light("light2", glm::vec3(0, 1, 0), LightType::AMBIENT);
	light2->translate(glm::vec3(3, 0, 4));
	light2->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light2->rotate(glm::radians(-135.0f), glm::vec3(0, 1, 0));
	//light2->setMesh(cubeMeshF);
	light2->setMaterial(lightMaterial);
	_world->add(light2);

	light->setAmbientContribution(0);
	light->SetLightIntensity(1);
	light->SetLightColor(color);

	light2->setAmbientContribution(1);
	light2->SetLightIntensity(1);
	light2->SetLightColor(glm::vec3(1, 1, 1));

	LitMaterial::AddLight(light);
	LitMaterial::AddLight(light2);

	camera->setBehaviour(new OrbitBehaviour(2, 90.0f, 5, *plane));
	glClearColor(0.2f, 0.9f, 1, 1);
}

void Assignment4::_render()
{
	AbstractGame::_render();
	_updateHud();
}

void Assignment4::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

Assignment4::~Assignment4()
{
	//dtor
}
