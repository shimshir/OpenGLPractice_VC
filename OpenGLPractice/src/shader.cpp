#include "shader.h"
#include <fstream>
#include <iostream>

void Shader::addShaderFromFile(ShaderType type, std::string shaderFilePath) {
    m_shaderFilePaths[type].push_back(shaderFilePath);
}

void Shader::remove(ShaderType type, std::string shaderFilePath) {
    int index = 0;
    for (std::string& shaderPath : m_shaderFilePaths[type]) {
        if (shaderFilePath == shaderPath)
            remove(type, index);
        index++;
    }
}

void Shader::remove(ShaderType type, int index) {
    m_shaderFilePaths[type].erase(m_shaderFilePaths[type].begin() + index);
}

void Shader::createAndCompile() {
    load();
    std::map<ShaderType, std::vector<std::string>>::iterator iter;

    for (iter = m_shaderSources.begin(); iter != m_shaderSources.end(); ++iter) {
        GLuint shader = glCreateShader(iter->first);
        m_shaders.push_back(shader);

		unsigned sizeo = (iter->second).size();
        char** sources = new char*[sizeo];
        for (unsigned i = 0; i < (iter->second).size(); i++) {
            sources[i] = (char*)(iter->second[i]).c_str();
        }

        glShaderSource(shader, 1, sources, &(m_shaderSourcesLengths[iter->first][0]));
        glCompileShader(shader);
        glAttachShader(m_program, shader);

        glBindAttribLocation(m_program, 0, "position");
        glBindAttribLocation(m_program, 1, "texCoord");
		glBindAttribLocation(m_program, 2, "normal");

        delete[] sources;
    }

}

void Shader::linkAndUse() {
    glLinkProgram(m_program);
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projection");
    glUseProgram(m_program);
	for (GLuint& shader : m_shaders) {
		glDetachShader(m_program, shader);
		glDeleteShader(shader);
	}
}

Shader::~Shader() {
	glDeleteProgram(m_program);
}

void Shader::load() {
    std::map<ShaderType, std::vector<std::string>>::iterator iter;

    for (iter = m_shaderFilePaths.begin(); iter != m_shaderFilePaths.end(); ++iter) {
        for (std::string& shaderPath : iter->second) {
            m_shaderSources[iter->first].push_back(readFile(shaderPath));
            m_shaderSourcesLengths[iter->first].push_back(readFile(shaderPath).length());
        }
    }
}

std::string Shader::readFile(std::string& filePath) {
    std::string line, shaderSource;

    std::ifstream shaderFile;
    shaderFile.open(filePath);
    if (shaderFile.is_open()) {
        while (getline(shaderFile, line))
            shaderSource.append(line + "\n");
        shaderFile.close();
    }
    return shaderSource;
}
void Shader::update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model_matrix = transform.getModelMatrix();
	glm::mat4 camera_projection_matrix = transform.getCameraMatrix(camera);

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model_matrix[0][0]);
	glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, GL_FALSE, &camera_projection_matrix[0][0]);
}
