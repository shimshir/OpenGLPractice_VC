#include "model.h"

Model::Model(std::vector<glm::vec3> positions, std::vector<glm::vec2> texCoords, std::vector<GLuint> indices) {
    this->m_positions = positions;
    this->m_texCoords = texCoords;
    this->m_indices = indices;
	this->m_normals = { positions.size(), glm::vec3(0.0, 0.0, 0.0) };
    this->calcNormals();
}

void Model::operator=(Model& model) {
    this->m_positions = model.getPositions();
    this->m_texCoords = model.getTexCoords();
    this->m_normals = model.getNormals();
    this->m_indices = model.getIndices();
}

void Model::calcNormals() {

    for (unsigned int i = 0; i < m_indices.size(); i += 3) {
        int i0 = m_indices.at(i);
        int i1 = m_indices.at(i + 1);
        int i2 = m_indices.at(i + 2);

        glm::vec3 v1 = m_positions.at(i1) - m_positions.at(i0);
        glm::vec3 v2 = m_positions.at(i2) - m_positions.at(i0);

        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

        m_normals.at(i0) += normal;
        m_normals.at(i1) += normal;
        m_normals.at(i2) += normal;
    }

    for (unsigned int i = 0; i < m_positions.size(); i++)
        m_normals.at(i) = glm::normalize(m_normals.at(i));
}

