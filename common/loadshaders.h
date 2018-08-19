#pragma once

// Inclut GLEW. Toujours l'inclure avant gl.h et glfw.h, car c'est un peu magique.
#include <GL/glew.h>

// Inclut GLFW
#include <GLFW/glfw3.h>

// Inclut GLM
#include <glm/glm.hpp>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
