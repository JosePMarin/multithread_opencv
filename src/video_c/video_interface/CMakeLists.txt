
# Declare the libraries
add_library(videoflow STATIC
        videoflow.cpp
)

#link the libraries in depencendy of this one
target_link_libraries(videoflow
    PUBLIC
    libprocess
)

# Specify the include directories exported by the libraries
target_include_directories(videoflow 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)



add_subdirectory(video_base)
add_subdirectory(process_frame)