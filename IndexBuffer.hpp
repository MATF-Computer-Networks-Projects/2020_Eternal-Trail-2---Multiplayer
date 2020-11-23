#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IndexBuffer {
private:
    unsigned int m_RendererID; //index buffer object ID
    unsigned int m_Count; //how many indices
public:
    //makes index buffer object, supplies it with data and binds it
    IndexBuffer(const unsigned int* data, unsigned int count);
    //deletes index buffer object
    ~IndexBuffer();

    //binds index buffer object
    void Bind() const;
    //unbinds index buffer object
    void Unbind() const;

    inline unsigned int GetCount() const;
};

#endif //INDEXBUFFER_HPP
