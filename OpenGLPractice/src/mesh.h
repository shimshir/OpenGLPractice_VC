#ifndef MESH_H
#define MESH_H

#include <string>
#include "model.h"
#include "glew.h"

enum MeshBufferIndices {
    POSITION_VB,
    TEXCOORD_VB,
    NORMAL_VB,
    INDEX_VB,

    NUMBER_OF_VERTEX_BUFFERS
};

class Mesh {
public:
    Mesh(const std::string& fileName);
    Mesh(Model& model);
    void draw();
    virtual ~Mesh();
protected:
private:
    GLuint m_vao, m_vbo[NUMBER_OF_VERTEX_BUFFERS], m_ebo;
    Model m_model;
};

#endif
