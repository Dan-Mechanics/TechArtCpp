#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <glad/glad.h>

const char* resourceDirectory = "res/";

void loadFromFile(std::string url, char*& buf) {
	std::ifstream stream(resourceDirectory + url, std::ios::binary);

	stream.seekg(0, stream.end);
	std::streamoff total = stream.tellg();
	buf = new char[total + 1];

	stream.seekg(0, stream.beg);
	stream.read(buf, total);

	buf[total] = '\0';

	stream.close();
}

std::string getFileContent(const std::string& path) {
    std::ifstream file{ path };
    if (!file.is_open())
        throw(errno);

    std::ostringstream filecontent;
    filecontent << file.rdbuf();
    return filecontent.str();
}

// utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
void checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}