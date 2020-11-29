#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

class Renderer {
private:

public:
    Renderer();
    ~Renderer();
    void Draw(const std::string& objectName);
};


#endif //RENDERER_HPP
