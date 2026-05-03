#include <iostream>	
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "utils.hpp"

const auto width = 800u;
const auto height = 700u;

const auto framerateLimit = 300;
const auto tickrate = 50;
const auto maxFrameInterval = 1.0 / framerateLimit;
const auto minTickInterval = 1.0f / tickrate;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

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

    const auto stride = 6 * sizeof(float);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    // colors.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
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
/// https://github.com/assimp/assimp
/// https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
/// https://youtu.be/O38kFTJiIYc?si=5-dekEgrKSK0pBrR
/// </summary>
int main() {
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
    
    auto previous = glfwGetTime();
    auto lastUpdateTime = glfwGetTime();
    auto updateTimer = 0.0;
    auto tickTimer = 0.0f;

    glfwSwapInterval(0);
    while (!glfwWindowShouldClose(window)) {
        const auto current = glfwGetTime();
        updateTimer += current - previous;
        previous = current;

        glfwPollEvents();
        if (updateTimer < maxFrameInterval)
            continue;

        const auto deltaTime = current - lastUpdateTime;
        lastUpdateTime = current;
        updateTimer = 0.0f;

        const auto title = "fps: " + std::to_string(round(1.0f / deltaTime));
        glfwSetWindowTitle(window, title.c_str());

        // UPDATE. ===
        processInput(window);

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

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}