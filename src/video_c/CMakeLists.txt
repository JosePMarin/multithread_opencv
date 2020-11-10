
# Declare the libraries
add_library(libprocess STATIC
        grey_scale.cpp
)

#link the libraries in depencendy of this one
target_link_libraries(libprocess
    PUBLIC
    libutils
    libvideo_base
    ${OpenCV_LIBS}
)

# Specify the include directories exported by the libraries
target_include_directories(libprocess 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


add_subdirectory(video_base)