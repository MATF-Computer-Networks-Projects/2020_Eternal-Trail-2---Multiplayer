#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {

    //initializing glfw
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }
    //setting up glfw version : 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //setting up core-profile mode
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //creating window object
    GLFWwindow* window = glfwCreateWindow(800,600,"Set The Stage!", NULL, NULL);
    if(window == NULL){
        std::cout << "Window creation failed!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    //setting up callback function which is called whenever the window changes in size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //setting up callback function for key press
    glfwSetKeyCallback(window, key_callback);

    //initializing glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //render loop
    while(!glfwWindowShouldClose(window)){

        //screen clearing color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //clearing the screen
        glClear(GL_COLOR_BUFFER_BIT);

        //double buffering: swaping the fron and back buffers
        glfwSwapBuffers(window);
        //checking if any events are triggered
        glfwPollEvents();
    }

    //destroying window
    glfwDestroyWindow(window);
    //cleaning up all the resources
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