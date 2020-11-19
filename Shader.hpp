#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:
    unsigned int programID;
    Shader(const  char * vertexShaderPath, const char * fragmentShaderPath);
    void use();

    //TODO Make one generic function instead of the following ones:
    void setBoolUniform(const std::string &name, bool value) const;
    void setIntUniform(const std::string &name, int value) const;
    void setFloatUniform(const std::string &name, float value) const;
    void setModelUniform(const std::string &name, glm::mat4 value) const;
    void setViewUniform(const std::string &name, glm::mat4 value) const;
    void setProjectionUniform(const std::string &name, glm::mat4 value) const;
};


#endif //SHADER_HPP
