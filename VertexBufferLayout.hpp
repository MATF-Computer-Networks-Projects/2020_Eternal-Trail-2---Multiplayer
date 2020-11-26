#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include <glad/glad.h>
#include <vector>

/* structure represents one element inside vertex buffer data
 * which can be vertices coordinates, color values, texture coordinates ...
 */
struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch (type) {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
            default: return 0;
        }
    }
};

//class used for building a vertex buffer layout out of given elements
class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout();
    inline unsigned int GetStride() const { return m_Stride;};
    inline const std::vector<VertexBufferElement>& GetElements() const {return m_Elements;};

    /* adds one element of specified type to layout's vector of elements
     * (there are several specializations of this template)
     */
    template<typename T>
    void Push(unsigned int count);

};


#endif //VERTEXBUFFERLAYOUT_HPP

