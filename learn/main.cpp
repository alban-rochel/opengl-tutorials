#include "GlfwWrapper.h"
#include "ShaderWrapper.h"
#include "generated.h"

int main(int, char**)
{
  GlfwWrapper wrapper;

  if(!wrapper.init())
  {
    return -1;
  }

  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW\n";
    return -1;
  }

  ShaderWrapper shaders;
  if(!shaders.compile(VERTEX_SHADER_FILE,
                      FRAGMENT_SHADER_FILE))
  {
    return -1;
  }

  glClearColor(.2f, .3f, .3f, 1.f);

  // define triangle
  float triangleVertices[] =
  {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
  }; // Normalized Device Coordinates (NDC)

  // Send to VertexBufferObject
  GLuint vbo;
  {
    glGenBuffers(1, &vbo); // create a buffer
#if 0
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // attach vbo as an array buffer

    // From this point on, functions apply to the current GL_ARRAY_BUFFER, i.e. vbo

    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(triangleVertices),
                 triangleVertices,
                 GL_STATIC_DRAW); // memcpy to current buffer

    glVertexAttribPointer(0 /* see location = 0 in vertex.vs */,
                          3 /* vec3 */,
                          GL_FLOAT /* vec3 */,
                          GL_FALSE /* do not normalize */,
                          3 * sizeof(float) /* stride: vec3, tightly packed */,
                          nullptr /* start offset */);

    glEnableVertexAttribArray(0 /* enable attribute at location 0 */);
#endif
  }

  // Wrap VBOs in a VertexArrayObject
  GLuint vao;
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // From this point on, functions apply to the current VAO, i.e. vao

    glBindBuffer(GL_ARRAY_BUFFER, vbo); // attach vbo as an array buffer

    // From this point on, functions apply to the current GL_ARRAY_BUFFER, i.e. vbo

    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(triangleVertices),
                 triangleVertices,
                 GL_STATIC_DRAW); // memcpy to current buffer

    glVertexAttribPointer(0 /* see location = 0 in vertex.vs */,
                          3 /* vec3 */,
                          GL_FLOAT /* vec3 */,
                          GL_FALSE /* do not normalize */,
                          3 * sizeof(float) /* stride: vec3, tightly packed */,
                          nullptr /* start offset */);

    glEnableVertexAttribArray(0 /* enable attribute at location 0 */);
  }

  while(!wrapper.shouldClose())
  {
    wrapper.processingLoopStart();

    glClear(GL_COLOR_BUFFER_BIT);

    shaders.use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    wrapper.processingLoopEnd();
  }

  glfwTerminate();

  return 0;
}
