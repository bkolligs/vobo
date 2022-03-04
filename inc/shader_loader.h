#ifndef _shader_loader_h_
#define _shader_loader_h_

#include "colored_output_strings.h"
#include <GL/glew.h>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct ShaderSource {
    std::string vertexSource;
    std::string fragmentSource;

    /* Overload the output operator for ease of use */
    friend std::ostream& operator<<(std::ostream& os,
                                    const ShaderSource& source);
};

class ShaderLoader {
   private:
    uint shaderCount_;
    bool verbose_;

   public:
    uint programID;
    ShaderLoader();
    ShaderLoader(const std::string& shaderFile, bool verbose = true);
    ~ShaderLoader();
    void activate();
    ShaderSource getFileContents(const std::string& fileName);
    uint compileShader(const std::string& source, uint type);
};

#endif  //_shader_loader_h_ header