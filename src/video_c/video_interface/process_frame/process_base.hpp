#pragma once
#include "video_instance.hpp"

class process_base 
{
    private:
        int m_device;
        std::string m_filename;
        video_base *m_base_ptr;
    public:
        cv::VideoCapture *capture_ptr;

    public:
        process_base(std::string &filename);
        process_base(int device);
        virtual ~process_base();
};