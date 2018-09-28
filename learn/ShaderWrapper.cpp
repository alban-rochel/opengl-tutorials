#include "ShaderWrapper.h"
#include <fstream>
#include <cassert>
#include <strings.h>

class ShaderWrapper::Private
{
  public:

    static bool LoadFile(const std::string& path, std::string& content) noexcept;

    bool loadShader(const std::string& path,
                    GLuint shaderType,
                    GLuint& shader) noexcept;

    GLuint _vertexShader = 0;
    GLuint _fragmentShader = 0;
    GLuint _program = 0;
};


bool ShaderWrapper::Private::LoadFile(const std::string& path,
                                      std::string& content) noexcept
{
  std::ifstream file(path);
  if(!file.is_open())
  {
    std::cerr << "Could not open " << path << std::endl;
    return false;
  }

  content.clear();

  while(file.good())
  {
    char buffer[500];
    bzero(buffer, 500);
    file.read(buffer,500);
    content.append(buffer);
  }

  file.close();

  return true;
}

bool ShaderWrapper::Private::loadShader(const std::string& path,
                                        GLuint shaderType,
                                        GLuint& shader) noexcept
{
  std::string shaderContentString;

  if(!Private::LoadFile(path, shaderContentString))
  {
    return false;
  }

  shader = glCreateShader(shaderType);

  const GLchar* shaderChar = shaderContentString.data();
  glShaderSource(shader,
                 1,
                 &shaderChar,
                 nullptr);

  glCompileShader(shader);

  int success;
  glGetShaderiv(shader,
                GL_COMPILE_STATUS,
                &success);
  if(!success)
  {
    int logLength;
    glGetShaderiv(shader,
                  GL_INFO_LOG_LENGTH,
                  &logLength);

    char* log = new char[logLength];
    glGetShaderInfoLog(shader,
                       512,
                       nullptr,
                       log);
    std::cerr << "Failed compiling " << path
              << ": " << log << std::endl;

    delete[] log;

    return false;
  }

  return true;
}

ShaderWrapper::ShaderWrapper() noexcept:
  _private(new Private)
{}

ShaderWrapper::~ShaderWrapper() noexcept
{}

bool ShaderWrapper::compile(const std::string& vertexShaderFile,
                            const std::string& fragmentShaderFile) noexcept
{
  assert(_private);
  assert(_private->_vertexShader == 0);
  assert(_private->_fragmentShader == 0);
  assert(_private->_program == 0);

  if(!_private->loadShader(vertexShaderFile,
                           GL_VERTEX_SHADER,
                           _private->_vertexShader))
  {
    return false;
  }

  if(!_private->loadShader(fragmentShaderFile,
                           GL_FRAGMENT_SHADER,
                           _private->_fragmentShader))
  {
    return false;
  }

  _private->_program = glCreateProgram();
  glAttachShader(_private->_program, _private->_vertexShader);
  glAttachShader(_private->_program, _private->_fragmentShader);
  glLinkProgram(_private->_program);
  {
    int success;
    glGetShaderiv(_private->_program,
                  GL_LINK_STATUS,
                  &success);
    if(!success)
    {
      int logLength;
      glGetShaderiv(_private->_program,
                    GL_INFO_LOG_LENGTH,
                    &logLength);

      char* log = new char[logLength];

      glGetShaderInfoLog(_private->_program,
                         512,
                         nullptr,
                         log);
      std::cerr << "Failed linking: " << log << std::endl;

      glDeleteShader(_private->_vertexShader);
      glDeleteShader(_private->_fragmentShader);

      delete[] log;

      return false;
    }
  }

  glDeleteShader(_private->_vertexShader);
  glDeleteShader(_private->_fragmentShader);

  return true;
}

bool ShaderWrapper::use() noexcept
{
  assert(_private);
  assert(_private->_program);

  glUseProgram(_private->_program);

  return true;
}

void ShaderWrapper::setUniformFloat(const GLchar* uniformName,
                                    float value) noexcept
{
  assert(_private);
  assert(_private->_program);

  int location = glGetUniformLocation(_private->_program, uniformName);
  glUniform1f(location, value);
}

void ShaderWrapper::setUniformInt(const GLchar* uniformName,
                                    GLuint value) noexcept
{
  assert(_private);
  assert(_private->_program);

  int location = glGetUniformLocation(_private->_program, uniformName);
  glUniform1i(location, value);
}
