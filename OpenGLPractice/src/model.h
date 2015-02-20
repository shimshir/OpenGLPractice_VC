#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "glew/glew.h"
#include "glm/glm.hpp"


class Model {
public:
	Model() = default;
	Model(std::vector<glm::vec3> positions,
		std::vector<glm::vec2> texCoords,
		std::vector<GLuint> indices);

	void operator=(Model& model);
	std::vector<glm::vec3>& getPositions() {
		return m_positions;
	};
	std::vector<glm::vec2>& getTexCoords() {
		return m_texCoords;
	};
	std::vector<GLuint>& getIndices() {
		return m_indices;
	};
	std::vector<glm::vec3>& getNormals() {
		return m_normals;
	};
private:
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec2> m_texCoords;
	std::vector<GLuint> m_indices;
	std::vector<glm::vec3> m_normals;
	void calcNormals();
};

#endif // MODEL_H
