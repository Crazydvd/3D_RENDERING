#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"
#include <SFML/Window.hpp>

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TerrainMaterial : public AbstractMaterial
{
public:
	TerrainMaterial(Texture* pSplatMap, Texture* pHeightMapTexture, Texture* pDiffuse1, Texture* pDiffuse2, Texture* pDiffuse3, Texture* pDiffuse4, glm::vec3 pSpecularColor = glm::vec3(1, 1, 1));
	virtual ~TerrainMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setSplatTexture(Texture* pSplatMap);
	void setHeightMapTexture(Texture* pHeightMap);


	void setSpecularColor(glm::vec3 pSpecularColor);
	void setOverrideSpecularColor(bool pOverride);

	void setMaxTerrainHeight(float pMaxHeight);

protected:
private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMVPMatrix;
	static GLint _uSplatMap;
	static GLint _uHeightMapTexture;

	static GLint _uDiffuse1;
	static GLint _uDiffuse2;
	static GLint _uDiffuse3;
	static GLint _uDiffuse4;

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	Texture* _splatMap;
	Texture* _heightMapTexture;
	
	Texture* _diffuse1;
	Texture* _diffuse2;
	Texture* _diffuse3;
	Texture* _diffuse4;

	sf::Clock _clock;

	//this one is unique per instance of color material
	glm::vec3 _ambientColor;
	glm::vec3 _specularColor;

	int _shininess = 1;

	bool _overrideSpecularLight = false;
	float _maxTerrainHeight = 1;

	TerrainMaterial(const TerrainMaterial&);
	TerrainMaterial& operator=(const TerrainMaterial&);
};

#endif // TEXTUREMATERIAL_HPP
