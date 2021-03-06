#pragma once

#include "learn_common.h"
#include <memory>

class ShaderWrapper
{
  public:

    ShaderWrapper() noexcept;

    ~ShaderWrapper() noexcept;

    bool compile(const std::string& vertexShaderFile,
                 const std::string& fragmentShaderFile) noexcept;

    bool use() noexcept;

    void setUniformFloat(const GLchar* uniformName,
                         float value) noexcept;

    void setUniformInt(const GLchar* uniformName,
                       GLuint value) noexcept;

    void setUniformMat4(const GLchar* uniformName,
                       const glm::mat4& value) noexcept;

  private:
    class Private;
    std::unique_ptr<Private>_private;
};
