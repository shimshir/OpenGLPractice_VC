#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <vector>
#include <map>
#include <glew.h>

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
    virtual ~Shader();
protected:
private:
    std::map<ShaderType, std::vector<std::string>> m_shaderFilePaths;
    std::map<ShaderType, std::vector<std::string>> m_shaderSources;
    std::map<ShaderType, std::vector<GLint>> m_shaderSourcesLengths;
    std::vector<GLuint> m_shaders;
    GLuint m_program;
    std::string readFile(std::string& filePath);

    void load();
};

#endif // SHADER_H
