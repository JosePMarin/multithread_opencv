

add_executable( videoflow 
    main.cpp
)

target_include_directories( videoflow
    PUBLIC
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries( videoflow
    PRIVATE
    ${OpenCV_LIBS}
    stdc++fs
)