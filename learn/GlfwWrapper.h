#pragma once

#include "learn_common.h"

class GlfwWrapper
{
  public:

    GlfwWrapper() noexcept;

    ~GlfwWrapper() noexcept;

    bool init() noexcept;

    inline bool shouldClose() noexcept
    {
      if(!_window)
        return true;

      return glfwWindowShouldClose(_window);
    }

    void processingLoopStart() noexcept;

    void processingLoopEnd() noexcept;

  protected:

    static void ErrorCallback(int error, const char* description);

    static void FrameBufferSizeCallback(GLFWwindow*, int w, int h);

    void ProcessInput() noexcept;

    GLFWwindow* _window = nullptr;
};
