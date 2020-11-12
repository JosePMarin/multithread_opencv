#include "load_frames.hpp"

void load_frames::proc_init (std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in)
{
    cv::Mat frame;
    while((*m_capture_ptr).isOpened())
    {
        std::scoped_lock lock(m_mutex);
        // Capture frame-by-frame
        try
        {
            (*m_capture_ptr).read(frame);
            // If the frame is empty, break immediately
            // otherwise load into buffer and notify
            if (!frame.empty())
            {
                (*buffer_out).push_back(std::move(frame));
            } else {
                break;
            }
        }
        catch(const cv::Exception& e)
        {
            std::cerr << e.what() << '\n';
            break;
        }
    }
}

    
load_frames::load_frames(video_instance *base_ptr)
{
    m_capture_ptr = base_ptr->capture_ptr;
}

void load_frames::do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                std::shared_ptr<object_queue<cv::Mat>> buffer_in)
{
    proc_init(buffer_out, buffer_in);
}

load_frames::~load_frames() {}