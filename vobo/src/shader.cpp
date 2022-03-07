#include "shader.h"

/* Print out the shader source struct nicely */
std::ostream& operator<<(std::ostream& os, const ShaderSource& source) {
    os << "Vertex Source:\n"
       << source.vertexSource << "Fragment Source:\n"
       << source.fragmentSource;
    return os;
}

Shader::Shader() {}
Shader::Shader(const std::string& shaderFile, bool verbose) : verbose_{verbose} {
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
        GLint result = 0;
        glGetProgramiv(programID_, GL_LINK_STATUS, (int*)&result);
        if (result == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(programID_, GL_INFO_LOG_LENGTH, &maxLength);
            /* the maxlength includes the NULL char */
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(programID_, maxLength, &maxLength, &infoLog[0]);

			/* Don't need the program anymore */
            glDeleteProgram(programID_);

            /* Don't leak the failed artifacts */
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

        }
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

Shader::~Shader() {  glDeleteProgram(programID_); }
void Shader::bind() const { glUseProgram(programID_); }

uint Shader::compileShader(const std::string& source, uint type) {
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

        std::stringstream errorMessage;
        errorMessage << VOBO_ERROR_STRING(
                            "[Shader] Failed to compile shader of type: ")
                     << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                     << std::endl
                     << message << std::endl;
        throw(std::runtime_error(errorMessage.str()));
    }
    return id;
}

ShaderSource Shader::getFileContents(const std::string& fileName) {
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

        verbose_ and VOBO_DEBUG_LOG("[Shader] Loaded shaders from: " << fileName);
        return {contents.at(0).str(), contents.at(1).str()};
    }

    else {
        char message[40 + fileName.size()];
        sprintf(message, VOBO_ERROR_STRING("[Shader] Unable to open file: '%s'"),
                fileName.c_str());
        throw std::invalid_argument(message);
    }
}

int Shader::getUniformLocation(const std::string&name) {
    /* Check if we have cached the uniform and if so access the hash map */
    if (uniformCache_.find(name) != uniformCache_.end()) {
        return uniformCache_[name];
    }
    /* Get the uniform location in the current shader program */
    int location = glGetUniformLocation(programID_, name.c_str());
    if (location == -1) {
        VOBO_ERROR_LOG("Could not find uniform: " << name);
    }

    verbose_ and std::cout << "[Shader] Caching uniform: " << name << std::endl;
	/* Cache the uniform */
    uniformCache_[name] = location;
    return location;
}

void Shader::setUniform4F(const std::string& name, float v0, float v1, float v2, float v3) {
    /* Set the uniform at the location we gather */
    int location = getUniformLocation(name);
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::setUniform1F(const std::string& name, float v0) {
    int location = getUniformLocation(name);
    glUniform1f(location, v0);
}

void Shader::setUniformMat4F(const std::string& name, glm::mat4& matrix) {
    int location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

}

void Shader::setUniformInt(const std::string& name, int v0) {
    int location = getUniformLocation(name);
    glUniform1i(location, v0);
}