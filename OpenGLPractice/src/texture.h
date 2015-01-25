#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "glew.h"

class Texture
{
public:
	Texture(const std::string& filePath);
	void bind();

	virtual ~Texture();
private:
	GLuint m_texture;
};

#endif //TEXTURE_H