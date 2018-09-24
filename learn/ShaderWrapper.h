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

  private:
    class Private;
    std::unique_ptr<Private>_private;
};
