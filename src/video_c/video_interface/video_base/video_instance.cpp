#include "video_instance.hpp"

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
    m_base_ptr = new video_base(m_device);
    capture_ptr = m_base_ptr->get_capture();
}

video_instance::video_instance(std::string &filename) : m_filename{filename} 
{
    m_base_ptr = new video_base(m_filename);
    capture_ptr = m_base_ptr->get_capture();
}

video_instance::~video_instance(){}