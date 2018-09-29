#include "GlfwWrapper.h"
#include "ShaderWrapper.h"
#include "generated.h"
#include "stb_image.h"

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
     0.5f,  0.5f,  0.5f, // front: top right
     0.5f, -0.5f,  0.5f, // front: bottom right
    -0.5f, -0.5f,  0.5f, // front: bottom left
    -0.5f,  0.5f,  0.5f, // front: top left
     0.5f,  0.5f, -0.5f, // back: top right
     0.5f, -0.5f, -0.5f, // back: bottom right
    -0.5f, -0.5f, -0.5f, // back: bottom left
    -0.5f,  0.5f, -0.5f, // back: top left
  }; // Normalized Device Coordinates (NDC)

  float colours[] {
    1.0f, 0.0f, 0.0f, // red
    0.0f, 1.0f, 0.0f, // green
    0.0f, 0.0f, 1.0f, // blue
    1.0f, 1.0f, 0.0f, // yellow
    1.0f, 0.0f, 0.0f, // red
    0.0f, 1.0f, 0.0f, // green
    0.0f, 0.0f, 1.0f, // blue
    1.0f, 1.0f, 0.0f, // yellow
  };

  unsigned int indices[] =
  {
    0, 1, 3,  // first triangle
    1, 2, 3,   // second triangle
    4, 5, 0,
    5, 1, 0,
    7, 6, 4,
    6, 5, 4,
    3, 2, 7,
    2, 6, 7,
    4, 3, 7,
    4, 0, 3,
    1, 2, 6,
    1, 6, 5
  };

  /*float texture_coords_0[] = {
    1.0f, 1.0f,  // top-right corner
    1.0f, 0.0f,  // bottom-right corner
    0.0f, 0.0f,  // bottom-left corner
    0.0f, 1.0f,  // top-left corner

  };*/
  float texture_coords_0[] = {
    0.5f, 0.5f,  // top-right corner
    0.5f, 0.0f,  // bottom-right corner
    0.0f, 0.0f,  // bottom-left corner
    0.0f, 0.5f,  // top-left corner
    1.0f, 1.0f,  // top-right corner
    1.0f, 0.0f,  // bottom-right corner
    0.5f, 0.5f,  // bottom-left corner
    0.0f, 1.0f,  // top-left corner
  };

  /*float texture_coords_1[] = {
     1.2f,  1.2f,  // top-right corner
     1.2f, -0.2f,  // bottom-right corner
    -0.2f, -0.2f,  // bottom-left corner
    -0.2f,  1.2f,  // top-left corner
  };*/
  float texture_coords_1[] = {
     0.5f,  0.5f,  // top-right corner
     0.5f, -0.2f,  // bottom-right corner
    -0.2f, -0.2f,  // bottom-left corner
    -0.2f,  0.5f,  // top-left corner
     1.2f,  1.2f,  // top-right corner
     1.2f, -0.2f,  // bottom-right corner
     0.5f,  0.5f,  // bottom-left corner
    -0.2f,  1.2f,  // top-left corner
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

  GLuint texture0, textureCoordVbo0;
  {
    glGenTextures(1, &texture0);
    glGenBuffers(1, &textureCoordVbo0);
  }

  GLuint texture1, textureCoordVbo1;
  {
    glGenTextures(1, &texture1);
    glGenBuffers(1, &textureCoordVbo1);
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

    // Bind texture 0
    {
      int width, height, nrChannels;
      unsigned char *data = stbi_load(TEXTURE_FILE_0, &width, &height, &nrChannels, 0);

      if(data)
      {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D,
                     0 /*mipmap level*/,
                     GL_RGB /*stored format*/,
                     width, height,
                     0 /*legacy*/,
                     GL_RGB /*in format*/,
                     GL_UNSIGNED_BYTE /*in format*/,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D); // autogenerate

        glBindBuffer(GL_ARRAY_BUFFER, textureCoordVbo0); // attach vbo as an array buffer

        // From this point on, functions apply to the current GL_ARRAY_BUFFER, i.e. vbo

        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(texture_coords_0),
                     texture_coords_0,
                     GL_STATIC_DRAW); // memcpy to current buffer

        glVertexAttribPointer(2,
                              2 /* vec2 */,
                              GL_FLOAT /* vec2 */,
                              GL_FALSE /* do not normalize */,
                              2 * sizeof(float) /* vec2, tightly packed*/,
                              nullptr /* start offset */);
        glEnableVertexAttribArray(2);
      }
      else
      {
        std::cerr << "Failed loading texture 0\n";
      }

      stbi_image_free(data);
    }

    // Bind texture 1
    {
      int width, height, nrChannels;
      unsigned char *data = stbi_load(TEXTURE_FILE_1, &width, &height, &nrChannels, 0);

      if(data)
      {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D,
                     0 /*mipmap level*/,
                     GL_RGB /*stored format*/,
                     width, height,
                     0 /*legacy*/,
                     GL_RGBA /*in format*/,
                     GL_UNSIGNED_BYTE /*in format*/,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D); // autogenerate

        glBindBuffer(GL_ARRAY_BUFFER, textureCoordVbo1); // attach vbo as an array buffer

        // From this point on, functions apply to the current GL_ARRAY_BUFFER, i.e. vbo

        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(texture_coords_1),
                     texture_coords_1,
                     GL_STATIC_DRAW); // memcpy to current buffer

        glVertexAttribPointer(3,
                              2 /* vec2 */,
                              GL_FLOAT /* vec2 */,
                              GL_FALSE /* do not normalize */,
                              2 * sizeof(float) /* vec2, tightly packed*/,
                              nullptr /* start offset */);
        glEnableVertexAttribArray(3);
      }
      else
      {
        std::cerr << "Failed loading texture 1\n";
      }

      stbi_image_free(data);
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

  glm::mat4 view = glm::translate(glm::identity<glm::mat4>(),
                                  glm::vec3(0.0f, 0.0f, -3.0f));
  glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                          800.f / 600.f,
                                          0.1f,
                                          100.0f);

  shaders.use();
  shaders.setUniformInt("ourTexture1", 0);
  shaders.setUniformInt("ourTexture2", 1);
  shaders.setUniformMat4("view", view);
  shaders.setUniformMat4("projection", projection);

  while(!wrapper.shouldClose())
  {
    wrapper.processingLoopStart();

    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 model = glm::rotate(glm::identity<glm::mat4>(),
                                  (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 0.5f, 0.0f));

    shaders.use();
    shaders.setUniformFloat("time", glfwGetTime());
    shaders.setUniformMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,
                   36 /* number of vertices */,
                   GL_UNSIGNED_INT /* type of indices */,
                   0 /* null offset */);

    wrapper.processingLoopEnd();
  }

  glfwTerminate();

  return 0;
}
