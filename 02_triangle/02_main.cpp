// Inclut les en-têtes standards
#include <stdio.h>
#include <stdlib.h>

// Inclut GLEW. Toujours l'inclure avant gl.h et glfw.h, car c'est un peu magique.
#include <GL/glew.h>

// Inclut GLFW
#include <GLFW/glfw3.h>

// Inclut GLM
#include <glm/glm.hpp>

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

int main()
{
  // Initialise GLFW
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

  // Ouvre une fenêtre et crée son contexte OpenGl
  GLFWwindow* window; // (Dans le code source qui accompagne, cette variable est globale)
  window = glfwCreateWindow( 800, 600, "Tutorial 01", nullptr, nullptr);
  if( window == nullptr )
  {
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window); // Initialise GLEW
  glewExperimental=true; // Nécessaire dans le profil de base
  if (glewInit() != GLEW_OK)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // This will identify our vertex buffer
  GLuint vertexbuffer;
  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);
  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  do
  {
    // Ne dessine rien, on se voit dans le tutoriel 2 !

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Vérifie si on a appuyé sur la touche échap (ESC) ou si la fenêtre a été fermée
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0 );
}
