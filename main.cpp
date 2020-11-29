#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <iostream>

#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"

#define WIDTH 800
#define HEIGHT 600

#define ASSERT(x) if(!(x)) exit(EXIT_FAILURE);
#define GLCall(f) \
    do{           \
        GL_ClearError(); \
        f;        \
        ASSERT(GL_LogError(__FILE__, __LINE__))\
    }while(0)

static void GL_ClearError(){
    while (glGetError() != GL_NO_ERROR);
}
static bool GL_LogError(const char* file, int line){
    if (GLenum error = glGetError()){
        std::cout << "[OpenGL Error] (0x0" << std::hex << error << std::dec << "): "  <<
                        file << " line: " << line << std::endl;
        return false;
    }
    return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


void ThreadWindowFunction(){
    //create window object
    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"Set The Stage of Etrenal Solitude!", NULL, NULL);
    if(window == NULL){
        std::cout << "Window creation failed!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    //set up callback function which is called whenever the window changes in size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //set up callback function for key press
    glfwSetKeyCallback(window, key_callback);

    //initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //make Shader object:
    //read shader scripts, compile them, create program object and link shaders to it
    Shader shader("../shader.vertex", "../shader.fragment");

    glEnable(GL_DEPTH_TEST);

    //define positions and color of cube vertices
    float vertices[] = {
             //position           //color
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
    };


    //create vertex buffer and vertex array and set vertex buffer layout
    VertexArray va;
    auto* vb = new VertexBuffer(vertices, sizeof(vertices));
    auto* layout = new VertexBufferLayout();
    layout->Push<float>(3); //first 3 floats represent vertex coordinates
    layout->Push<float>(3); //next 3 floats represent color value for corresponding vertex
    va.AddBuffer(*vb, *layout); //set layout of vertex buffer


    float plate1_trans = 0;
    float plate2_trans = -1;
    float ghost_border = 1.5;

    //render loop
    while(!glfwWindowShouldClose(window)){

        //screen clearing color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //use our program object with linked shaders
        shader.use();

        //GLM: set up view and projection matrices
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        view  = glm::lookAt(glm::vec3(0,1,4), glm::vec3(0,0,0), glm::vec3(0,1,0));
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        //set corresponding uniforms in vertex shader
        shader.setViewUniform("view", view);
        shader.setProjectionUniform("projection", projection);


        //bind vertex array
        va.Bind();

        if(plate1_trans >= ghost_border)
            plate1_trans = -1 + plate2_trans;
        if(plate2_trans >= ghost_border)
            plate2_trans = -1 + plate1_trans;



        //draw first path plate
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4, 0.125, 100));
        model = glm::translate(model, glm::vec3(0, -0.5, -0.5+plate1_trans));
        shader.setModelUniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //draw middle obstacle relative to the plate [no reset of model matrix!]
        model = glm::scale(model, glm::vec3(1.0/4, 1.0/0.125, 1.0/100));
        model = glm::translate(model, glm::vec3(0, 0.5, 0));
        shader.setModelUniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //draw second path plate
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(4, 0.125, 100));
        model = glm::translate(model, glm::vec3(0, -0.5, -0.5+plate2_trans));
        shader.setModelUniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //draw middle obstacle relative to the plate [no reset of model matrix!]
        model = glm::scale(model, glm::vec3(1.0/4, 1.0/0.125, 1.0/100));
        model = glm::translate(model, glm::vec3(0, 0.5, 0));
        shader.setModelUniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        plate1_trans += 0.002;
        plate2_trans += 0.002;

        //double buffering: swap the front and back buffers
        glfwSwapBuffers(window);
        //check if any events are triggered
        glfwPollEvents();
    }

    //destroy window
    glfwDestroyWindow(window);

    delete(vb);
    delete(layout);
}

int main() {

    //initialize GLFW
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }
    //set up GLFW version : 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //set up core-profile mode
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::thread window1(ThreadWindowFunction);
    std::thread window2(ThreadWindowFunction);

    window1.join();
    window2.join();

    //terminates the GLFW library
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}