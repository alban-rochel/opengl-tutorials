set(COMMON opengl_common)

set(COMMON_SRC
    loadshaders.cpp
    texture.cpp
    )

add_library(${COMMON} SHARED ${COMMON_SRC})

target_link_libraries(${COMMON}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  )
