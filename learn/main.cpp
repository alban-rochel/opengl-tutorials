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

  {
    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    std::cout << "Renderer: " << renderer <<"\n";
    std::cout << "OpenGL version supported " << version << "\n";
  }

  ShaderWrapper shaders;
  if(!shaders.compile(VERTEX_SHADER_FILE,
                      FRAGMENT_SHADER_FILE))
  {
    return -1;
  }

  glClearColor(.2f, .3f, .3f, 1.f);

  // define vertices
  float vertices[] =
  {
     0.5f,  0.5f,  0.0f, // top right
     0.5f, -0.5f,  0.0f, // bottom right
    -0.5f, -0.5f,  0.0f, // bottom left
    -0.5f,  0.5f,  0.0f, // top left
  }; // Normalized Device Coordinates (NDC)

  float colours[] {
    1.0f, 0.0f, 0.0f, // red
    0.0f, 1.0f, 0.0f, // green
    0.0f, 0.0f, 1.0f, // blue
    1.0f, 1.0f, 0.0f, // yellow
  };

  unsigned int indices[] =
  {
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
  };

  // Send to VertexBufferObject
  GLuint vbo;
  {
    glGenBuffers(1, &vbo); // create a buffer
  }

  GLuint colour_vbo;
  {
    glGenBuffers(1, &colour_vbo); // create a buffer
  }

  // Element buffer object
  GLuint ebo;
  {
    glGenBuffers(1, &ebo);
  }

  // Wrap VBOs in a VertexArrayObject
  GLuint vao;
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // From this point on, functions apply to the current VAO, i.e. vao

    // Set up Vertices VBO
    {
      glBindBuffer(GL_ARRAY_BUFFER, vbo); // attach vbo as an array buffer

      // From this point on, functions apply to the current GL_ARRAY_BUFFER, i.e. vbo

      glBufferData(GL_ARRAY_BUFFER,
                   sizeof(vertices),
                   vertices,
                   GL_STATIC_DRAW); // memcpy to current buffer

      glVertexAttribPointer(0 /* see location = 0 in vertex.vs */,
                            3 /* vec3 */,
                            GL_FLOAT /* vec3 */,
                            GL_FALSE /* do not normalize */,
                            3 * sizeof(float) /* stride: vec3, tightly packed */,
                            nullptr /* start offset */);

      glEnableVertexAttribArray(0 /* enable attribute at location 0 */);
    }

    // Set up Colours VBO
    {
      glBindBuffer(GL_ARRAY_BUFFER, colour_vbo); // attach vbo as an array buffer

      // From this point on, functions apply to the current GL_ARRAY_BUFFER, i.e. vbo

      glBufferData(GL_ARRAY_BUFFER,
                   sizeof(colours),
                   colours,
                   GL_STATIC_DRAW); // memcpy to current buffer

      glVertexAttribPointer(1,
                            3 /* vec3 */,
                            GL_FLOAT /* vec3 */,
                            GL_FALSE /* do not normalize */,
                            3 * sizeof(float) /* stride: vec3, tightly packed */,
                            nullptr /* start offset */);

      glEnableVertexAttribArray(1 /* enable attribute at location 1 */);
    }

    // Set up EBO
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   sizeof(indices),
                   indices,
                   GL_STATIC_DRAW);
    }
  }

  while(!wrapper.shouldClose())
  {
    wrapper.processingLoopStart();

    glClear(GL_COLOR_BUFFER_BIT);

    shaders.use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,
                   6 /* number of vertices */,
                   GL_UNSIGNED_INT /* type of indices */,
                   0 /* null offset */);

    wrapper.processingLoopEnd();
  }

  glfwTerminate();

  return 0;
}
