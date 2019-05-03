#include "glm.hpp"

#include "TerrainMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "3d_rendering_asign_4/config.hpp"

ShaderProgram* TerrainMaterial::_shader = NULL;

GLint TerrainMaterial::_uMVPMatrix = 0;
GLint TerrainMaterial::_uSplatMap = 0;
GLint TerrainMaterial::_uHeightMapTexture = 0;

GLint TerrainMaterial::_uDiffuse1 = 0;
GLint TerrainMaterial::_uDiffuse2 = 0;
GLint TerrainMaterial::_uDiffuse3 = 0;
GLint TerrainMaterial::_uDiffuse4 = 0;

GLint TerrainMaterial::_aVertex = 0;
GLint TerrainMaterial::_aNormal = 0;
GLint TerrainMaterial::_aUV = 0;

TerrainMaterial::TerrainMaterial(Texture* pSplatMap, Texture* pHeightMapTexture, Texture* pDiffuse1, Texture* pDiffuse2, Texture* pDiffuse3, Texture* pDiffuse4, glm::vec3 pSpecularColor) : _splatMap(pSplatMap), _heightMapTexture(pHeightMapTexture), _diffuse1(pDiffuse1), _diffuse2(pDiffuse2), _diffuse3(pDiffuse3), _diffuse4(pDiffuse4), _specularColor(pSpecularColor)
{
	_lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::_lazyInitializeShader()
{
	if (!_shader)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::ASSIGNMENT4_SHADER_PATH + "terrain.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::ASSIGNMENT4_SHADER_PATH + "terrain.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uSplatMap = _shader->getUniformLocation("splatMap");
		_uHeightMapTexture = _shader->getUniformLocation("heightMapTexture");
		_uDiffuse1 = _shader->getUniformLocation("diffuse1");
		_uDiffuse2 = _shader->getUniformLocation("diffuse2");
		_uDiffuse3 = _shader->getUniformLocation("diffuse3");
		_uDiffuse4 = _shader->getUniformLocation("diffuse4");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}

void TerrainMaterial::setSplatTexture(Texture* pDiffuseTexture)
{
	_splatMap = pDiffuseTexture;
}

void TerrainMaterial::setHeightMapTexture(Texture* pHeightMapTexture)
{
	_heightMapTexture = pHeightMapTexture;
}

void TerrainMaterial::setSpecularColor(glm::vec3 pSpecularColor)
{
	_specularColor = glm::vec3(pSpecularColor);
	setOverrideSpecularColor(true);
}

void TerrainMaterial::setOverrideSpecularColor(bool pOverride)
{
	_overrideSpecularLight = pOverride;
}

void TerrainMaterial::setMaxTerrainHeight(float pMaxHeight)
{
	_maxTerrainHeight = pMaxHeight;
}

void TerrainMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	if (!_splatMap) return;

	_shader->use();

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _splatMap->getId());
	//tell the shader the texture slot for the Splatmap texture is slot 0
	glUniform1i(_uSplatMap, 0);

	//setup texture slot 1
	glActiveTexture(GL_TEXTURE1);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _heightMapTexture->getId());
	//tell the shader the texture slot for the Heightmap texture is slot 1
	glUniform1i(_uHeightMapTexture, 1);

	//setup texture slot 2
	glActiveTexture(GL_TEXTURE2);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuse1->getId());
	//tell the shader the texture slot for the diffuse1 texture is slot 2
	glUniform1i(_uDiffuse1, 2);

	//setup texture slot 3
	glActiveTexture(GL_TEXTURE3);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuse2->getId());
	//tell the shader the texture slot for the diffuse2 texture is slot 3
	glUniform1i(_uDiffuse2, 3);

	//setup texture slot 4
	glActiveTexture(GL_TEXTURE4);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuse3->getId());
	//tell the shader the texture slot for the diffuse3 texture is slot 4
	glUniform1i(_uDiffuse3, 4);

	//setup texture slot 5
	glActiveTexture(GL_TEXTURE5);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuse4->getId());
	//tell the shader the texture slot for the diffuse4 texture is slot 5
	glUniform1i(_uDiffuse4, 5);


	//set the material color
	glUniform1i(_shader->getUniformLocation("shininess"), _shininess);
	glUniform1f(_shader->getUniformLocation("maxHeight"), _maxTerrainHeight);
	glUniform1i(_shader->getUniformLocation("lightCount"), LitMaterial::GetLightCount());

	//pass in the time to the shader
	glUniform1f(_shader->getUniformLocation("time"), _clock.getElapsedTime().asSeconds());

	glm::vec3 specularColor = _specularColor;

	std::vector<Light*> _lights = LitMaterial::getLights();

	//pass in the light properties
	for (size_t i = 0; i < _lights.size(); i++)
	{
		if (!_overrideSpecularLight)
		{
			specularColor = _lights[i]->GetColor();
		}

		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].specularColor"), 1, glm::value_ptr(specularColor));

		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightColor"), 1, glm::value_ptr(_lights[i]->GetColor()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].ambientLightColor"), 1, glm::value_ptr(_lights[i]->GetAmbientColor()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightPosition"), 1, glm::value_ptr(_lights[i]->GetPosition()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightForward"), 1, glm::value_ptr(_lights[i]->GetForwardDirection()));
		glUniform1i(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightType"), _lights[i]->GetType());
		glUniform1f(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].falloff"), _lights[i]->getFalloff());

		//spotLight properties
		if (_lights[i]->GetType() == LightType::SPOT)
		{
			glUniform1f(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].coneAngle"), _lights[i]->GetConeAngle());
			glUniform1f(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].fallOffAngle"), _lights[i]->GetFallOffAngle());
		}
	}

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
