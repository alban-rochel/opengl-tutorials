set(03_MATRICES 03_matrices)

set(03_MATRICES_SRC
    03_main.cpp
    )

add_executable(${03_MATRICES} ${03_MATRICES_SRC})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleFragmentShader.fragmentshader ${CMAKE_CURRENT_BINARY_DIR}/SimpleFragmentShader.fragmentshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleVertexShader.vertexshader ${CMAKE_CURRENT_BINARY_DIR}/SimpleVertexShader.vertexshader COPYONLY)


target_link_libraries(${03_MATRICES}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  opengl_common
  )
