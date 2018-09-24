#include "GlfwWrapper.h"
#include <cassert>

class GlfwWrapper::Private
{
  public:
    static void ErrorCallback(int error, const char* description)
    {
      std::cerr << "Error " << error << ": " << description << "\n";
    }

    static void FrameBufferSizeCallback(GLFWwindow*, int w, int h)
    {
      glViewport(0, 0, w, h);
    }

    void ProcessInput() noexcept
    {
      assert(_window);

      if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
        glfwSetWindowShouldClose(_window, true);
      }
    }

    GLFWwindow* _window = nullptr;
};

GlfwWrapper::GlfwWrapper() noexcept:
  _private(new Private)
{
  glfwSetErrorCallback(Private::ErrorCallback);
}

GlfwWrapper::~GlfwWrapper() noexcept
{
  glfwTerminate();
}

bool GlfwWrapper::init() noexcept
{
  assert(_private);
  assert(!_private->_window);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _private->_window = glfwCreateWindow(800, 600, "Pwet", nullptr, nullptr);

  if(!_private->_window)
  {
    return false;
  }

  glfwMakeContextCurrent(_private->_window);

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(_private->_window, Private::FrameBufferSizeCallback);

  return true;
}

void GlfwWrapper::processingLoopStart() noexcept
{
  assert(_private);

  _private->ProcessInput();
}

void GlfwWrapper::processingLoopEnd() noexcept
{
  assert(_private);
  assert(_private->_window);

  glfwSwapBuffers(_private->_window);
  glfwPollEvents();
}

bool GlfwWrapper::shouldClose() noexcept
{
  assert(_private);
  assert(_private->_window);

  return glfwWindowShouldClose(_private->_window);
}
