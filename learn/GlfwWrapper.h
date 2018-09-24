#pragma once

#include "learn_common.h"
#include <memory>

class GlfwWrapper
{
  public:

    GlfwWrapper() noexcept;

    ~GlfwWrapper() noexcept;

    bool init() noexcept;

    bool shouldClose() noexcept;

    void processingLoopStart() noexcept;

    void processingLoopEnd() noexcept;

  private:

    class Private;
    std::unique_ptr<Private> _private;
};
