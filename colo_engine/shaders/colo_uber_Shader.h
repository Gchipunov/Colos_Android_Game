#ifndef COLO_GAME_SHADER_H
#define COLO_GAME_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>

class Shader
{
public:
    GLuint ID;

    // constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void InitShader();
	
    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const GLfloat *value) const;

	std::vector <std::string> vectorStringsShaderTemplates;
	
	int addShaderTemplate(const char *szString);
	int addShaderTemplate(std::string stringString);
	

	
	std::string vertexCode;
    std::string fragmentCode;
	

	
	
private:
    void checkCompileErrors(GLuint shader, std::string type);
	
	void ShaderStringReplace(std::string &text, std::string replacement);
	
	
	
};

#endif
