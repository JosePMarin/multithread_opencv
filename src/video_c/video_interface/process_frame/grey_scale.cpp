#include "grey_scale.hpp"

void grey_scale::proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in)
{
    while (true)
    {
        std::scoped_lock lock(m_mutex);
        if ((*buffer_in).empty() && !(*m_capture_ptr).isOpened())
            break;
        if (!(*buffer_in).empty()) 
        {
            auto temp_frame = (*buffer_in).pop_front();
            cv::cvtColor(temp_frame, temp_frame, cv::COLOR_BGR2GRAY);
            (*buffer_out).push_back(std::move(temp_frame));
        }
    }
}

grey_scale::grey_scale(process_base *base_ptr)
{
    m_capture_ptr = base_ptr->capture_ptr;
}

void grey_scale::do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in)
{
    proc_init(buffer_out, buffer_in);
}