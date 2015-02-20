#ifndef ASSIMP_WRAPPER_H
#define ASSIMP_WRAPPER_H
#include <string>
#include <iostream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

class AssimpWrapper {
private:
	std::vector<Mesh*> m_meshes;
	void processScene(const aiScene* scene);
	bool loadModelFile(const std::string& file_path);
public:
	std::vector<Mesh*>& getMeshes(const std::string& file_path);
	~AssimpWrapper() {
		for (Mesh* mesh : m_meshes)
			delete mesh;
	}
};

#endif