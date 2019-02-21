#include "glm.hpp"

#include "LitMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "3d_rendering_asign_3/config.hpp"

ShaderProgram* LitMaterial::_shader = NULL;
Light* LitMaterial::Light = NULL;

LitMaterial::LitMaterial(glm::vec3 pAmbientColor, glm::vec3 pDiffuseColor) :_diffuseColor(pDiffuseColor), _ambientColor(pAmbientColor)
{
	//every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
	_lazyInitializeShader();
}

void LitMaterial::_lazyInitializeShader()
{
	//this shader contains everything the material can do (it can render something in 3d using a single color)
	if (!_shader) 
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::ASSIGNMENT3_SHADER_PATH + "lit.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::ASSIGNMENT3_SHADER_PATH + "lit.fs");
		_shader->finalize();
	}
}

LitMaterial::~LitMaterial()
{
	//dtor
}

void LitMaterial::setDiffuseColor(glm::vec3 pDiffuseColor)
{
	_diffuseColor = pDiffuseColor;
}

void LitMaterial::setAmbientColor(glm::vec3 pAmbientColor)
{
	_ambientColor = pAmbientColor;
}


void LitMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	_shader->use();

	//set the material color
	glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));
	glUniform3fv(_shader->getUniformLocation("ambientLightColor"), 1, glm::value_ptr(LitMaterial::Light->GetAmbientColor()));
	glUniform3fv(_shader->getUniformLocation("lightPosition"), 1, glm::value_ptr(LitMaterial::Light->getWorldPosition()));
	glUniform3fv(_shader->getUniformLocation("lightColor"), 1, glm::value_ptr(LitMaterial::Light->GetColor()));

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);

}
