#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game.h"

int main(void)
{
    GLFWwindow* window;
    game game;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 1024, "Welcome to the spaghetti-land", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Error";
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    /* Loop until the user closes the window */
    glOrtho(-130.0, 150.0, -150.0, 150.0, -1.5, 1.5);
    glScalef(0.7, -0.7, 0);
    while (!glfwWindowShouldClose(window))
    {
        game.GameplayLoop(window);
    }
    glfwTerminate();
    return 0;
}