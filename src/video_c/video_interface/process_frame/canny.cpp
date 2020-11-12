#include "canny.hpp"

void canny::proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
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
            cv::Canny(temp_frame, temp_frame, 0, 30, 3);
            (*buffer_out).push_back(std::move(temp_frame));
        }
    }
}

canny::canny(video_instance *p_video_instance)
        {
            m_capture_ptr = p_video_instance->capture_ptr;
        }

void canny::do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in)
        {
            proc_init(buffer_out, buffer_in);
        }

canny::~canny() {}