#include "VertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {

    Bind(); //bind vertex array
    vb.Bind(); //bind vertex buffer
    const auto& elements = layout.GetElements(); //get elements inside layout
    int offset = 0; //set offset for first element inside vertex buffer to zero

    for(unsigned int i=0; i<elements.size(); i++){

        const auto& element = elements[i]; //get next element
        glEnableVertexAttribArray(i); //enable layout for current element

        //define layout for current element
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
                              layout.GetStride(), (void*)offset);

        //update offset for the next element in vertex buffer
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}
