#include "mesh.h"

Mesh::Mesh(const std::string& fileName) {

}

Mesh::Mesh(Model& model) {
    m_model = model;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(NUMBER_OF_VERTEX_BUFFERS, m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.getPositions().size() * sizeof(model.getPositions().at(0)), &model.getPositions().at(0), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.getTexCoords().size() * sizeof(model.getTexCoords().at(0)), &model.getTexCoords().at(0), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.getNormals().size() * sizeof(model.getNormals().at(0)), &model.getNormals().at(0), GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.getIndices().size() * sizeof(model.getIndices().at(0)), &model.getIndices().at(0), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::draw() {
    glBindVertexArray(m_vao);
    glDrawElementsBaseVertex(GL_TRIANGLES, m_model.getIndices().size(), GL_UNSIGNED_INT, 0, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteBuffers(NUMBER_OF_VERTEX_BUFFERS, m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}
