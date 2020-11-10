# Declare the libraries
add_library(libutils 
    INTERFACE
)

#link the libraries in depencendy of this one
target_link_libraries(libutils
    INTERFACE
    ${OpenCV_LIBS}
)

# Specify the include directories exported by the libraries
target_include_directories(libutils
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)