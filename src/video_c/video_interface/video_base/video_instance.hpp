#pragma once
#include "video_base.hpp"


class video_instance
{
private:
    static video_instance* m_instance;
    int m_device;
    std::string m_filename;

public:
    video_base *base_ptr;

private:
    video_instance(int device);
    video_instance(std::string &filename);
public:
    static video_instance* get_instance(int device);
    static video_instance* get_instance(std::string &filename);
    ~video_instance();
};




