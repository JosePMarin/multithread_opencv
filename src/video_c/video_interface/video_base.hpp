#pragma once

#include "common.hpp"

class video_base
{
private:
    std::experimental::filesystem::path m_pwd;
    std::string m_path;
    int m_device;
    cv::VideoCapture m_cap;
private:
    
    template <typename T> 
    void init(T arg);
    

public:
    video_base(int device);
    
    video_base(std::string &filename);

    cv::VideoCapture *get_capture ();

    virtual ~video_base() {}

};
