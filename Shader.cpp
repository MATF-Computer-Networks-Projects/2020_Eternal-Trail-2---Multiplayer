#include "Shader.hpp"

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {

    std::string vShaderCode;
    std::string  fShaderCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    //ensure ifstrem can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    //retrieve the vertex/fragment source code
    try {
        //open files
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);

        std::stringstream vShaderStream;
        std::stringstream fShaderStream;

        //read file content
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //close files
        vShaderFile.close();
        fShaderFile.close();
        //convert stream into string
        vShaderCode = vShaderStream.str();
        fShaderCode = fShaderStream.str();

    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::File_not_succesfully_read" << std::endl;
    }

    const char* vShaderCode_c = vShaderCode.c_str();
    const char * fShaderCode_c = fShaderCode.c_str();
    int success;
    char infoLog[512];

    //compile vertex shader
    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode_c, NULL);
    glCompileShader(vertex);
    //check vertex shader complitaion errors
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
                << "\n----------------------------- " << std::endl;
    }

    //compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode_c, NULL);
    glCompileShader(fragment);
    //check fragment shader complitaion errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED:\n" << infoLog
                  << "\n----------------------------- " << std::endl;
    }

    //create program
    programID = glCreateProgram();
    //attach vertex and fragment shaders
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    //check linking errors
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR:\n" << infoLog
                << "\n----------------------------- " << std::endl;
    }

    //delete vertex and fragment shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(programID);
}

void Shader::setBoolUniform(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setIntUniform(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloatUniform(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setModelUniform(const std::string &name, glm::mat4 value) const {
    int modelLocation = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setViewUniform(const std::string &name, glm::mat4 value) const {
    int viewLocation = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setProjectionUniform(const std::string &name, glm::mat4 value) const {
    int projectionLocation = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(value));
}
