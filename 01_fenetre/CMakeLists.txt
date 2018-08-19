set(01_FENETRE 01_fenetre)

set(01_FENETRE_SRC
    01_main.cpp
    )

add_executable(${01_FENETRE} ${01_FENETRE_SRC})

target_link_libraries(${01_FENETRE}
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  )
