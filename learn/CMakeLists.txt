set(LEARN learn)

set(LEARN_SRC
    GlfwWrapper.cpp
    main.cpp
    )

add_executable(${LEARN} ${LEARN_SRC})

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleFragmentShader.fragmentshader ${CMAKE_CURRENT_BINARY_DIR}/SimpleFragmentShader.fragmentshader COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleVertexShader.vertexshader ${CMAKE_CURRENT_BINARY_DIR}/SimpleVertexShader.vertexshader COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/uvtemplate.DDS ${CMAKE_CURRENT_BINARY_DIR}/uvtemplate.DDS COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cube.obj ${CMAKE_CURRENT_BINARY_DIR}/cube.obj COPYONLY)


target_link_libraries(${LEARN}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  )
