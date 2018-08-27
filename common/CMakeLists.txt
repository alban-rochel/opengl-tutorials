set(COMMON opengl_common)

set(COMMON_SRC
    loadshaders.cpp
    texture.cpp
    controls.cpp
    objloader.cpp
    )

add_library(${COMMON} SHARED ${COMMON_SRC})

target_link_libraries(${COMMON}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  )

#set(CONTROLS opengl_controls)

#set(CONTROLS_SRC
#    controls.cpp
#    )

#add_library(${CONTROLS} SHARED ${CONTROLS_SRC})

#target_link_libraries(${CONTROLS}
#  ${GLEW_LIBRARIES}
#  ${GLFW_LIBRARIES}
#  )
