set(04_CUBE 04_cube)

set(04_CUBE_SRC
    04_main.cpp
    )

add_executable(${04_CUBE} ${04_CUBE_SRC})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleFragmentShader.fragmentshader ${CMAKE_CURRENT_BINARY_DIR}/SimpleFragmentShader.fragmentshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleVertexShader.vertexshader ${CMAKE_CURRENT_BINARY_DIR}/SimpleVertexShader.vertexshader COPYONLY)


target_link_libraries(${04_CUBE}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  opengl_common
  )
