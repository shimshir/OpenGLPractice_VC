#ifndef ASSIMP_WRAPPER_H
#define ASSIMP_WRAPPER_H
#include <string>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

class AssimpWrapper {
private:
	Mesh* m_mesh;
	void processScene(const aiScene* scene);
public:
	bool loadModelFile(const std::string& file_path);
	Mesh* getMesh();
};

#endif