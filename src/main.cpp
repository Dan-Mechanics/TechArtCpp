#include <iostream>	
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "utils.hpp"

void processInput(GLFWwindow* window);

GLuint createTriangle() {
    // id in video memory, reference with pointers.
    GLuint vao; // vertex array object.
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,   1, 0, 0,
        0.5f, -0.5f, 0.0f,   0, 1, 0,
        0.0f,  0.5f, 0.0f,  0, 0, 1
    };

    const auto stide = 6 * sizeof(float);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stide, 0);
    glEnableVertexAttribArray(0);

    // colors.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stide, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return vao;
}

GLuint createShaders() {
    char* vertexSource;
    char* fragmentSource;
    loadFromFile("default.vert", vertexSource);
    loadFromFile("default.frag", fragmentSource);

    // ===

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertexSource, nullptr);
    glCompileShader(vert);
    checkCompileErrors(vert, "VERTEX");

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragmentSource, nullptr);
    glCompileShader(frag);
    checkCompileErrors(frag, "FRAGMENT");

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);

    glLinkProgram(program);
    checkCompileErrors(program, "PROGRAM");

    return program;
}

/// <summary>
/// TODO:
/// max framerate, like in minectaft clone
/// https://github.com/assimp/assimp
/// </summary>
int main() {
    const auto width = 800;
    const auto height = 600;
    const std::clock_t startClock = std::clock();
    auto startTime = std::chrono::high_resolution_clock::now();

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

    // create assets
    GLuint triangle = createTriangle();
    GLuint diffuse = createShaders();
    
    while (!glfwWindowShouldClose(window)) {
        // INPUT.
        processInput(window);

        auto currTime = std::chrono::high_resolution_clock::now();

        // RENDER.
        glClearColor(0.5f, 0.2f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(diffuse);
        glBindVertexArray(triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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