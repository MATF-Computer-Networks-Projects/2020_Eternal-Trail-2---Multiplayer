#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    //method sets layout of given vertex buffer according to specified layout
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    //binds Vertex Array
    void Bind() const;
    //unbinds Vertex Array
    void Unbind() const;
};


#endif //VERTEXARRAY_HPP
