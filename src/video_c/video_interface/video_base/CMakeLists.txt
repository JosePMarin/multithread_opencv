  
# Declare the libraries
add_library(libvideo_interface STATIC
        video_base.cpp
        video_instance.cpp
)

#link the libraries in depencendy of this one
target_link_libraries(libvideo_interface
    PUBLIC
    libutils
)

# Specify the include directories exported by the libraries
target_include_directories(libvideo_interface 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)