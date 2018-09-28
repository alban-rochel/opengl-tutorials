set(LEARN learn)

set(LEARN_SRC
    GlfwWrapper.cpp
    ShaderWrapper.cpp
    stb_image.cpp
    main.cpp
    )

add_executable(${LEARN} ${LEARN_SRC})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/generated.h.in ${CMAKE_CURRENT_BINARY_DIR}/generated.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vertex.vs ${CMAKE_CURRENT_BINARY_DIR}/vertex.vs COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fragment.fs ${CMAKE_CURRENT_BINARY_DIR}/fragment.fs COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png COPYONLY)

target_link_libraries(${LEARN}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  )

target_include_directories(${LEARN}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
