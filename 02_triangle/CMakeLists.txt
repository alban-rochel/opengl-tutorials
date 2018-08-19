set(02_TRIANGLE 02_triangle)

set(02_TRIANGLE_SRC
    02_main.cpp
    )

add_executable(${02_TRIANGLE} ${02_TRIANGLE_SRC})

target_link_libraries(${02_TRIANGLE}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  )
