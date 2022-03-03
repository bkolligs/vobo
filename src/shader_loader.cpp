#include "shader_loader.h"

/* Print out the shader source struct nicely */
std::ostream& operator<<(std::ostream& os, const ShaderSource& source) {
    os << "Vertex Source:\n"
       << source.vertexSource << "Fragment Source:\n"
       << source.fragmentSource;
    return os;
}

ShaderLoader::ShaderLoader() {}
ShaderLoader::ShaderLoader(const std::string& shaderFile, bool verbose) {
    try {
        /* Load the shaders into the strings */
        ShaderSource shaderSource = getFileContents(shaderFile);

        /* compile the vertex shader */
        uint vertexShader =
            compileShader(shaderSource.vertexSource, GL_VERTEX_SHADER);

        /* compile the fragment shader */
        uint fragmentShader =
            compileShader(shaderSource.fragmentSource, GL_FRAGMENT_SHADER);

        // Create Shader Program Object and get its reference
        programID_ = glCreateProgram();
        // Attach the Vertex and Fragment Shaders to the Shader Program
        glAttachShader(programID_, vertexShader);
        glAttachShader(programID_, fragmentShader);
        /* Wrap-up/Link all the shaders together into the Shader Program */
        glLinkProgram(programID_);
        /* Validate the program */
        glValidateProgram(programID_);

        // Delete the now useless Vertex and Fragment Shader objects
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

ShaderLoader::~ShaderLoader() {}
void ShaderLoader::activate() { glUseProgram(programID_); }
void ShaderLoader::deactivate() { glDeleteProgram(programID_); }

uint ShaderLoader::compileShader(const std::string& source, uint type) {
    /* Create a shader of the type specified */
    uint id = glCreateShader(type);
    const char* src = source.c_str();
    /* Define the shader source file */
    glShaderSource(id, 1, &src, NULL);
    /* Compile the shader */
    glCompileShader(id);
    /* Check for errors during shader compilation */
    int result;
    /* Get the shader compile information */
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        /* Get the shader compile results information */
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << "shader!" << std::endl;
        std::cout << message << std::endl;
    }
    return id;
}

ShaderSource ShaderLoader::getFileContents(const std::string& fileName) {
    std::ifstream input(fileName, std::ios::binary);
    /* The point of this is to index into our content vector */
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    /* We will create a struct for each shader */
    if (input) {
        uint shaderCount = 0;
        std::string line;
        ShaderType curType = ShaderType::NONE;
        /* Create an array of the shaders */
        std::array<std::stringstream, 2> contents;
        /* Iterate through the lines of the file */
        while (getline(input, line)) {
            /* If we are dealing with an additional shader */
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    curType = ShaderType::VERTEX;
                } else if (line.find("fragment") != std::string::npos) {
                    curType = ShaderType::FRAGMENT;
                }
            } else {
                /* place the current line into the shader source */
                contents.at((int)curType) << line << "\n";
            }
        }

        verbose_ and std::cout
            << SUCCESS_INFO("[ShaderLoader] Loaded shaders from: ") << fileName
            << std::endl;
        return {contents.at(0).str(), contents.at(1).str()};
    }

    else {
        char message[40 + fileName.size()];
        sprintf(message, ERROR_INFO("[ShaderLoader] Unable to open file: '%s'"),
                fileName.c_str());
        throw std::invalid_argument(message);
    }
}