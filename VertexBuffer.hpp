#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
private:
    unsigned int m_RendererID; //vertex buffer object ID
public:
    //makes vertex buffer object, supplies it with data and binds it
    VertexBuffer(const void* data, unsigned int size);
    //deletes vertex buffer object
    ~VertexBuffer();

    //binds vertex buffer object
    void Bind() const;
    //unbinds vertex buffer object
    void Unbind() const;
};

#endif //VERTEXBUFFER_HPP
