#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:
    unsigned int programID;
    Shader(const  char * vertexShaderPath, const char * fragmentShaderPath);
    void use();

    //TODO Make one generic function insted of the folowing ones:
    void setBoolUniform(const std::string &name, bool value) const;
    void setIntUniform(const std::string &name, int value) const;
    void setFloatUniform(const std::string &name, float value) const;
};


#endif //SHADER_HPP
