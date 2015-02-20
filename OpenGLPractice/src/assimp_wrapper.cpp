#include "assimp_wrapper.h"
#include "glm/glm.hpp"
#include "util.h"
#include <iostream>

bool AssimpWrapper::loadModelFile(const std::string& file_path) {

	//Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(file_path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	// If the import failed, report it
	if (!scene) {
		std::cerr << importer.GetErrorString();
		return false;
	}
	// Now we can access the file's contents.
	processScene(scene, file_path);
	// We're done. Everything will be cleaned up by the importer destructor

	return true;
}

void AssimpWrapper::processScene(const aiScene* scene, const std::string& file_path) {

	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* ai_mesh = scene->mMeshes[i];
		Model m_model;
		for (int j = 0; j < ai_mesh->mNumFaces; j++) {
			const aiFace& face = ai_mesh->mFaces[j];
			for (int k = 0; k < 3; k++) {
				aiVector3D pos = ai_mesh->mVertices[face.mIndices[k]];
				aiVector3D uv = ai_mesh->HasTextureCoords(0) ? ai_mesh->mTextureCoords[0][face.mIndices[k]] : aiVector3D(0.0f, 0.0f, 0.0f);
				aiVector3D normal = ai_mesh->HasNormals() ? ai_mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);

				m_model.getPositions().push_back(glm::vec3(pos.x, pos.y, pos.z));
				m_model.getTexCoords().push_back(glm::vec2(uv.x, uv.y));
				m_model.getNormals().push_back(glm::vec3(normal.x, normal.y, normal.z));
			}
		}
		for (int q = 0; q < m_model.getPositions().size(); q++)
			m_model.getIndices().push_back(q);
		
		const aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
		aiString path;
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
			if (path.data != "") {
				std::string textureName = path.data;
				std::string dir = getDirectoryPath(file_path);
				std::string full_path = dir + "texture/" + textureName;
				m_meshes.push_back(new Mesh(m_model, full_path));
			}
		}
		else {
			m_meshes.push_back(new Mesh(m_model, "res/textures/placeholder.jpg"));
		}
	}
}

std::vector<Mesh*>& AssimpWrapper::getMeshes(const std::string& file_path) {
	loadModelFile(file_path);
	return m_meshes;
}