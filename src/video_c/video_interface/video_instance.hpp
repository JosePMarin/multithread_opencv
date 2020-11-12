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

/* Null, because instance will be initialized on demand. */
video_instance* video_instance::m_instance = 0;

video_instance* video_instance::get_instance(int device)
{
    if (m_instance == 0)
    {
        m_instance = new video_instance(device);
    }

    return m_instance;
}

video_instance* video_instance::get_instance(std::string &filename)
{
    if (m_instance == 0)
    {
        m_instance = new video_instance(filename);
    }

    return m_instance;
}

video_instance::video_instance(int device) : m_device{device}
{
    base_ptr = new video_base(m_device);
}

video_instance::video_instance(std::string &filename) : m_filename{filename} 
{
    base_ptr = new video_base(m_filename);
}

video_instance::~video_instance(){}


