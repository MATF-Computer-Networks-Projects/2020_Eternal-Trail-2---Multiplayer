#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {

    //initialize glfw
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }
    //set up glfw version : 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //set up core-profile mode
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create window object
    GLFWwindow* window = glfwCreateWindow(800,600,"Set The Stage!", NULL, NULL);
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

    //initialize glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //make Shader object:
    //read shader scripts, compile them, create program object and link shaders to it
    Shader shader("../shader.vertex", "../shader.fragment");

    //define positions and color of triangle vertices
    float vertices[] = {
            // positions         // colors
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    //create and bind buffers
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //fill buffer with vertices data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //specify position of vertices coordinates inside buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //specify position of vertices color values inside buffer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //GLM library test:
    glm::vec4 vec(1.0, 2.0, 3.0, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(2.0f, 2.0f, 2.0f));
    vec = trans * vec;
    std::cout << "Translated vector: " << vec.x << " " << vec.y << " " << vec.z << std::endl;
    

    //render loop
    while(!glfwWindowShouldClose(window)){

        //screen clearing color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        //use our program object with linked shaders
        shader.use();
        glBindVertexArray(VAO);
        //draw triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //double buffering: swap the front and back buffers
        glfwSwapBuffers(window);
        //check if any events are triggered
        glfwPollEvents();
    }

    //destroy window
    glfwDestroyWindow(window);
    //clean up all the resources
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