#include "colo_uber_Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    // 1. Retrieve the vertex/fragment source code from filePath
 //   std::string vertexCode;
  //  std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
	
	
 
	
	
}

//void Shader::ShaderStringReplace(std::string &vertexCode, std::string replacement)
void Shader::ShaderStringReplace(std::string &text, std::string replacement)
{
	const std::string to_replace = "[template]";
	
    // Find the first occurrence of the substring
    size_t pos = text.find(to_replace);

    // Loop until no more occurrences are found
    while (pos != std::string::npos) {
        // Replace the substring at the found position
        text.replace(pos, to_replace.length(), replacement);

        // Find the next occurrence, starting the search from after the last replacement
        pos = text.find(to_replace, pos + replacement.length());
    }
	
}
void Shader::InitShader()
{
	  // --- Method 1: Using a simple for-loop ---
    std::string combinedStringLoop = ""; // Initialize an empty string to store the result

    // Iterate through each string in the vector
    for (const std::string& s : vectorStringsShaderTemplates) {
        combinedStringLoop += s; // Append each string to the combined string
        combinedStringLoop += "\n"; // Optional: Add a newline after each part for readability
    }
	
	ShaderStringReplace(vertexCode,combinedStringLoop);
	
	
	const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Shader Program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);
    
    // Print linking errors if any
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
	
	
}

void Shader::use() 
{ 
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value); 
}
void Shader::setMat4(const std::string &name, const GLfloat *value) const
{ 
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, value);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}


	
	int Shader::addShaderTemplate(const char *szString)
	{
			vectorStringsShaderTemplates.push_back(szString);
	}
	
	int Shader::addShaderTemplate(std::string stringString)
	{
		
		vectorStringsShaderTemplates.push_back(stringString);
		
	}
	