#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TerrainMaterial : public AbstractMaterial
{
public:
	TerrainMaterial(Texture* pDiffuseTexture, glm::vec3 pSpecularColor = glm::vec3(1, 1, 1));
	virtual ~TerrainMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseTexture(Texture* pDiffuseTexture);
	void setSpecularColor(glm::vec3 pSpecularColor);
	void setOverrideSpecularColor(bool pOverride);

protected:
private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMVPMatrix;
	static GLint _uDiffuseTexture;

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	Texture* _diffuseTexture;

	//this one is unique per instance of color material
	glm::vec3 _ambientColor;
	glm::vec3 _specularColor;

	int _shininess = 4;

	bool _overrideSpecularLight = false;

	TerrainMaterial(const TerrainMaterial&);
	TerrainMaterial& operator=(const TerrainMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
