#include "blurr.hpp"

void blurr::proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
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
            cv::GaussianBlur(temp_frame, temp_frame, cv::Size(7,7), 1.5, 1.5);
            (*buffer_out).push_back(std::move(temp_frame));
        }
    }
}

blurr::blurr(process_base *base_ptr)
{
    m_capture_ptr = base_ptr->capture_ptr;
}

void blurr::do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in)
{
    proc_init(buffer_out, buffer_in);
}

blurr::~blurr() {}