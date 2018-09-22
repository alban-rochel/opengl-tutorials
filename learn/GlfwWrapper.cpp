#include "GlfwWrapper.h"

GlfwWrapper::GlfwWrapper() noexcept
{
  glfwSetErrorCallback(ErrorCallback);
}

GlfwWrapper::~GlfwWrapper() noexcept
{
  glfwTerminate();
}

bool GlfwWrapper::init() noexcept
{
  if(_window)
    return false;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(800, 600, "Pwet", nullptr, nullptr);

  if(!_window)
  {
    return false;
  }

  glfwMakeContextCurrent(_window);

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(_window, FrameBufferSizeCallback);

  return true;
}

void GlfwWrapper::processingLoopStart() noexcept
{
  ProcessInput();
}

void GlfwWrapper::processingLoopEnd() noexcept
{
  if(!_window)
    return;

  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void GlfwWrapper::ErrorCallback(int error, const char* description)
{
  std::cerr << "Error " << error << ": " << description << "\n";
}

void GlfwWrapper::FrameBufferSizeCallback(GLFWwindow*, int w, int h)
{
  glViewport(0, 0, w, h);
}

void GlfwWrapper::ProcessInput() noexcept
{
  if(!_window)
    return;

  if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(_window, true);
  }
}
