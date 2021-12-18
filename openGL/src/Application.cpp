#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game.h"
char pressedKey = ' ';
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_W) pressedKey = 'w';
        if (key == GLFW_KEY_A) pressedKey = 'a';
        if (key == GLFW_KEY_S) pressedKey = 's';
        if (key == GLFW_KEY_D) pressedKey = 'd';
    }
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
    glfwSetKeyCallback(window, key_callback);
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
        glfwPollEvents();
        game.GameplayLoop(window, pressedKey);
        pressedKey = NULL;
    }
    glfwTerminate();
    return 0;
}
