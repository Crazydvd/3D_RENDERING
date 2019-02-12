#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <GL/glew.h>

class Texture
{
	public:
		static Texture* load(const std::string pTexturePath);

		virtual ~Texture();

		GLuint getId();

	protected:

		//all previously loaded meshes;
		static std::map<std::string, Texture*> _textures;
        static Texture* _loadFromFile(const std::string pTexturePath);

	    //OpenGL id for texture buffer
		GLuint _id;

		Texture();

};

#endif // TEXTURE_HPP
