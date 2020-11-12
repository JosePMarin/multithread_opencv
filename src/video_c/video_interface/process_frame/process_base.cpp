#include "process_base.hpp"

process_base::process_base(std::string &filename) : m_filename{filename} 
{
    auto shared_video_instance = video_instance::get_instance(m_filename);
    m_base_ptr = shared_video_instance->base_ptr;
    capture_ptr = m_base_ptr->get_capture();
}
process_base::process_base(int device) : m_device{device}
{
    auto shared_video_instance = video_instance::get_instance(m_device);
    m_base_ptr = shared_video_instance->base_ptr;
    capture_ptr = m_base_ptr->get_capture();
}

process_base::~process_base(){}