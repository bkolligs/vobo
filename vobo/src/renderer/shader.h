#ifndef _shader_h_
#define _shader_h_

#include "log.h"
#include "vobo_pch.h"
#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderSource {
    std::string vertexSource;
    std::string fragmentSource;

    /* Overload the output operator for ease of use */
    friend std::ostream& operator<<(std::ostream& os,
                                    const ShaderSource& source);
};

class Shader {
   private:
    uint shaderCount_;
    bool verbose_;
    uint programID_;
    /* Place to store the locations of particular uniforms that have been found
     * already */
    std::unordered_map<std::string, int> uniformCache_;

   public:
    Shader();
    Shader(const std::string& shaderFile, bool verbose = true);
    ~Shader();
    void bind() const;
    ShaderSource getFileContents(const std::string& fileName);
    uint compileShader(const std::string& source, uint type);
    uint getProgramID() { return programID_; }
    int getUniformLocation(const std::string& name);
    /* Set a uniform of type 4 float, default color is white */
    void setUniform4F(const std::string& name, float v0, float v1, float v2,
                      float v3);
    void setUniform1F(const std::string& name, float v0);
    void setUniformMat4F(const std::string& name, const glm::mat4& matrix);
    void setUniformInt(const std::string& name, int v0);
};

#endif  //_shader_h_ header