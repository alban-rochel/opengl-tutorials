#include "GlfwWrapper.h"

int main(int, char**)
{
  GlfwWrapper wrapper;

  if(!wrapper.init())
  {
    return -1;
  }

  glClearColor(.2f, .3f, .3f, 1.f);

  while(!wrapper.shouldClose())
  {
    wrapper.processingLoopStart();

    glClear(GL_COLOR_BUFFER_BIT);

    wrapper.processingLoopEnd();
  }

  glfwTerminate();

  return 0;
}
