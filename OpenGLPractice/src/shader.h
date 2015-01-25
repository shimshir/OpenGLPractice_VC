#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <vector>
#include <map>
#include <glew.h>
#include "transform.h"

typedef int ShaderType;

class Shader {
public:
    Shader() {
        m_program = glCreateProgram();
    };
    void addShaderFromFile(ShaderType type, std::string shaderFilePath);
    void remove(ShaderType type, int);
    void remove(ShaderType type, std::string shaderFilePath);
    void createAndCompile();
    void linkAndUse();
	void update(const Transform& transform);
    virtual ~Shader();
protected:
private:
	std::string readFile(std::string& filePath);
    std::map<ShaderType, std::vector<std::string>> m_shaderFilePaths;
    std::map<ShaderType, std::vector<std::string>> m_shaderSources;
    std::map<ShaderType, std::vector<GLint>> m_shaderSourcesLengths;
    std::vector<GLuint> m_shaders;
	
    GLuint m_program;
    void load();

	enum
	{
		TRANSFORM_U,

		NUMBER_OF_UNIFORMS
	};
	GLuint m_uniforms[NUMBER_OF_UNIFORMS];
};

#endif // SHADER_H
