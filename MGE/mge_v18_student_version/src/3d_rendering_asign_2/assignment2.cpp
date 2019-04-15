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
#include "mge/materials/WobbleMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "3d_rendering_asign_2/config.hpp"
#include "3d_rendering_asign_2/assignment2.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
Assignment2::Assignment2() :AbstractGame(), _hud(0)
{
	glm::mat4 matrix(1);

	matrix = glm::rotate(matrix, glm::radians(45.0f), glm::vec3(0, 0, 1));
	matrix = glm::translate(matrix, glm::vec3(2, 4, 6));

	std::cout << "Camera" << std::endl << matrix << std::endl;

	matrix = glm::inverse(matrix); //inverse to get the view matrix.

	std::cout << "View" << std::endl << matrix << std::endl;

	//NOTE: you translate in local space, so you translate along the rotated axis.
}

void Assignment2::initialize()
{
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void Assignment2::_initializeScene()
{
	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* planeMeshDefault = Mesh::load(config::ASSIGNMENT2_MODEL_PATH + "plane.obj");
	Mesh* cubeMeshF = Mesh::load(config::ASSIGNMENT2_MODEL_PATH + "cube_flat.obj");
	Mesh* sphereMeshS = Mesh::load(config::ASSIGNMENT2_MODEL_PATH + "sphere_smooth.obj");

	Mesh* sphere1 = Mesh::load(config::ASSIGNMENT2_MODEL_PATH + "sphere1.obj"); //Doesn't work: vertex normals are not in the file (vn)
	Mesh* sphere2 = Mesh::load(config::ASSIGNMENT2_MODEL_PATH + "sphere2.obj"); //Works: UV is messed up
	Mesh* sphere3 = Mesh::load(config::ASSIGNMENT2_MODEL_PATH + "sphere3.obj"); //Doesn't work: UVs are not in the file (vt)
	Mesh* sphere4 = Mesh::load(config::ASSIGNMENT2_MODEL_PATH + "sphere4.obj"); //Works: Only half the Faces are rendered

	//MATERIALS

	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::ASSIGNMENT2_TEXTURE_PATH + "runicfloor.png"));

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
	plane->setMaterial(runicStoneMaterial);
	_world->add(plane);

	//add a spinning sphere
	GameObject* sphere;
	int i = 0;
	switch (i)
	{
	case 0:
		sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
		sphere->scale(glm::vec3(2.5, 2.5, 2.5));
		sphere->setMesh(sphereMeshS);
		sphere->setMaterial(new WobbleMaterial(Texture::load(config::ASSIGNMENT2_TEXTURE_PATH + "runicfloor.png")));
		//sphere->setBehaviour(new RotatingBehaviour());
		_world->add(sphere);
		break;
	case 1:
		sphere = new GameObject("sphere1", glm::vec3(0, 0, 0));
		sphere->scale(glm::vec3(2.5, 2.5, 2.5));
		sphere->setMesh(sphere1);
		sphere->setMaterial(runicStoneMaterial);
		sphere->setBehaviour(new RotatingBehaviour());
		_world->add(sphere);
		break;
	case 2:
		sphere = new GameObject("sphere2", glm::vec3(0, 0, 0));
		sphere->scale(glm::vec3(2.5, 2.5, 2.5));
		sphere->setMesh(sphere2);
		sphere->setMaterial(runicStoneMaterial);
		sphere->setBehaviour(new RotatingBehaviour());
		_world->add(sphere);
		break;
	case 3:
		sphere = new GameObject("sphere3", glm::vec3(0, 0, 0));
		sphere->scale(glm::vec3(2.5, 2.5, 2.5));
		sphere->setMesh(sphere3);
		sphere->setMaterial(runicStoneMaterial);
		sphere->setBehaviour(new RotatingBehaviour());
		_world->add(sphere);
		break;
	case 4:
		sphere = new GameObject("sphere4", glm::vec3(0, 0, 0));
		sphere->scale(glm::vec3(2.5, 2.5, 2.5));
		sphere->setMesh(sphere4);
		sphere->setMaterial(runicStoneMaterial);
		sphere->setBehaviour(new RotatingBehaviour());
		_world->add(sphere);
		break;
	}

	//add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
	//It's here as a place holder to get you started.
	//Note how the texture material is able to detect the number of lights in the scene
	//even though it doesn't implement any lighting yet!

	Light* light = new Light("light", glm::vec3(0, 4, 0));
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->setMesh(cubeMeshF);
	light->setMaterial(lightMaterial);
	light->setBehaviour(new KeysBehaviour(25));
	_world->add(light);


	camera->setBehaviour(new OrbitBehaviour(8, 60.0f, 5.0f, *sphere));
}

void Assignment2::_render()
{
	AbstractGame::_render();
	_updateHud();
}

void Assignment2::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

Assignment2::~Assignment2()
{
	//dtor
}
