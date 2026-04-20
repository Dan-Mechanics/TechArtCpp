#include <iostream>	
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window);

/// <summary>
/// https://learnopengl.com/Getting-started/Hello-Window
/// </summary>
int main() {
    const auto width = 800;
    const auto height = 600;
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Tech Art C++", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(window)) {
        // INPUT.
        processInput(window);

        // RENDER.
        glClearColor(0.5f, 0.2f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // SWAP AND POLL.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}