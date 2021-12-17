#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Welcome to the spaghetti-land", NULL, NULL);
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
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        glVertex2f(-0.25f, 0.25f); // top left
        glVertex2f(0.25f, 0.25f); // top right 
        glVertex2f(0.25f, -0.25f); // bottom right
        glVertex2f(-0.25f, -0.25f); // bottom left
        //glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}