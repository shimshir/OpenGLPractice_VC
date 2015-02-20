#ifndef MESH_H
#define MESH_H

#include <string>
#include <iostream>
#include "model.h"
#include "glew/glew.h"
#include "stb/stb_image.h"

enum MeshBufferIndices {
    POSITION_VB,
    TEXCOORD_VB,
    NORMAL_VB,
    INDEX_VB,

    NUMBER_OF_VERTEX_BUFFERS
};

class Mesh {
public:
	Mesh(Model& model);
	Mesh(Model& model, const std::string& texture_file_path);
	void draw();
	void setTexture(GLuint texture) { m_texture = texture; };
	
	virtual ~Mesh();
private:
	GLuint m_vao, m_vbo[NUMBER_OF_VERTEX_BUFFERS];
	GLuint m_sampler;
	GLuint m_texture;
	Model m_model;

	void initDataBuffers();
	void initTexture(const std::string& texture_file_path);
};

#endif
