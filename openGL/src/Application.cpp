#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game.h"

char GetKeyPress(GLFWwindow* window)
{
    int stateW = glfwGetKey(window, GLFW_KEY_W);
    if (stateW == GLFW_PRESS || stateW == GLFW_REPEAT)
    {
        return 'w';
    }
    int stateA = glfwGetKey(window, GLFW_KEY_A);
    if (stateA == (GLFW_PRESS || GLFW_REPEAT))
    {
        return 'a';
    }
    int stateS = glfwGetKey(window, GLFW_KEY_S);
    if (stateS == (GLFW_PRESS || GLFW_REPEAT))
    {
        return 's';
    }
    int stateD = glfwGetKey(window, GLFW_KEY_D);
    if (stateD == (GLFW_PRESS || GLFW_REPEAT))
    {
        return 'd';
    }
    return NULL;
}

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
        char keypressed = GetKeyPress(window);
        glfwPollEvents();
        game.GameplayLoop(window, keypressed);
    }
    glfwTerminate();
    return 0;
}