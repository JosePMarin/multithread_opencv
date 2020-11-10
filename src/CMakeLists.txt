add_executable( videoflow 
    main2.cpp
)

# target_include_directories( videoflow
#     PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/video_c
# )

target_link_libraries( videoflow
    PRIVATE
    libvideo_base
    libprocess
)

add_subdirectory(utils)
add_subdirectory(video_c)