  
# Declare the libraries
add_library(libvideo_base SHARED
        video_base.cpp
)

#link the libraries in depencendy of this one
target_link_libraries(libvideo_base
    PUBLIC
    libutils
    stdc++fs
    ${OpenCV_LIBS}
)

# Specify the include directories exported by the libraries
target_include_directories(libvideo_base 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)