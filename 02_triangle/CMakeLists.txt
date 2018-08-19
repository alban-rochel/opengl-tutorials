set(02_TRIANGLE 02_triangle)

set(02_TRIANGLE_SRC
    02_main.cpp
    )

add_executable(${02_TRIANGLE} ${02_TRIANGLE_SRC})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleFragmentShader.fragmentshader ${CMAKE_CURRENT_BINARY_DIR}/SimpleFragmentShader.fragmentshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleVertexShader.vertexshader ${CMAKE_CURRENT_BINARY_DIR}/SimpleVertexShader.vertexshader COPYONLY)


target_link_libraries(${02_TRIANGLE}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  opengl_common
  )
