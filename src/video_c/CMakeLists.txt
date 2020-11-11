
# Declare the libraries
add_executable(slam
        slam.cpp
)

#link the libraries in depencendy of this one
target_link_libraries(slam
    PUBLIC
    libutils
    libvideo_interface
)

# Specify the include directories exported by the libraries
target_include_directories(slam 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


add_subdirectory(video_interface)

