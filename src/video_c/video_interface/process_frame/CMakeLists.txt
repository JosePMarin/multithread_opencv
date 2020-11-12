  
# Declare the libraries
add_library(libprocess STATIC
        blurr.cpp
        canny.cpp
        display.cpp
        grey_scale.cpp
        load_frames.cpp
)

#link the libraries in depencendy of this one
target_link_libraries(libprocess
    PUBLIC
    libvideo_interface
)

# Specify the include directories exported by the libraries
target_include_directories(libprocess 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)