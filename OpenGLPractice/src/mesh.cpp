#include "mesh.h"

Mesh::Mesh(const std::string& obj_file_path) {

}

Mesh::Mesh(Model& model) {
	m_model = model;
	initDataBuffers();
}

Mesh::Mesh(Model& model, const std::string& texture_file_path) {
    m_model = model;
	initDataBuffers();
	initTexture(texture_file_path);
}

void Mesh::initDataBuffers() {
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(NUMBER_OF_VERTEX_BUFFERS, m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_model.getPositions().size() * sizeof(m_model.getPositions().at(0)), &m_model.getPositions().at(0), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_model.getTexCoords().size() * sizeof(m_model.getTexCoords().at(0)), &m_model.getTexCoords().at(0), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_model.getNormals().size() * sizeof(m_model.getNormals().at(0)), &m_model.getNormals().at(0), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.getIndices().size() * sizeof(m_model.getIndices().at(0)), &m_model.getIndices().at(0), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::initTexture(const std::string& texture_file_path) {
	int width, height, num_components;
	unsigned char* image_data = stbi_load(texture_file_path.c_str(), &width, &height, &num_components, 4);
	if (image_data == NULL)
		std::cerr << "Texture loading failed for texture: " << texture_file_path << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	stbi_image_free(image_data);
}

void Mesh::draw() {
    glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_2D, m_texture);
    glDrawElementsBaseVertex(GL_TRIANGLES, m_model.getIndices().size(), GL_UNSIGNED_INT, 0, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteBuffers(NUMBER_OF_VERTEX_BUFFERS, m_vbo);
    glDeleteVertexArrays(1, &m_vao);
	glDeleteTextures(1, &m_texture);
}
