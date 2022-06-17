add_executable(
    c1i
    main.cpp
    assembly_builder.cpp
    runtime.cpp
    assembly_builder.h
    runtime.h
)

target_link_libraries(
    c1i 
    ${C1RECOGNIZER_LIBS} 
    ${IRBACKEND_LIBS}
)

install(
    TARGETS c1i
    RUNTIME DESTINATION bin
)
