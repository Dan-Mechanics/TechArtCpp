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

    const auto maxFramerate = 60;
    const auto maxFrameInterval = 1.0 / maxFramerate;
    double previousTime = 0;
    double lastFrameTime = 0;
     // https://stackoverflow.com/questions/57800608/how-to-render-at-a-fixed-fps-in-a-glfw-window
    // This while loop repeats as fast as possible
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - previousTime;

        glfwPollEvents();

        // update your application logic here,
        // using deltaTime if necessary (for physics, tweening, etc.)

        // This if-statement only executes once every 60th of a second
        if (currentTime - lastFrameTime >= maxFrameInterval) {
            // RENDER.
            glClearColor(0.5f, 0.2f, 0.9f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);

            // only set lastFrameTime when you actually draw something
            lastFrameTime = currentTime;
        }

        // set lastUpdateTime every iteration
        previousTime = currentTime;
    }

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