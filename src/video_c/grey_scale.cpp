#include "grey_scale.hpp"

grey_scale::grey_scale(int device) : video_base{device}
{
    processed_buffer = std::make_shared<FrameQueue<cv::Mat>>();
}
    
grey_scale::grey_scale(std::string &filename) : video_base{filename}
{
    processed_buffer = std::make_shared<FrameQueue<cv::Mat>>();
}

void grey_scale::grey_scale_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer)
{
    while (true)
    {
        std::scoped_lock lock(base_mutex);
        if ((*load_buffer).empty() && !cap.isOpened())
            break;
        if (!(*load_buffer).empty()) 
        {
            auto temp_frame = (*load_buffer).pop_front();
            cv::cvtColor(temp_frame, temp_frame, cv::COLOR_BGR2GRAY);
            cv::GaussianBlur(temp_frame, temp_frame, cv::Size(7,7), 1.5, 1.5);
            cv::Canny(temp_frame, temp_frame, 0, 30, 3);
            (*buffer).push_back(std::move(temp_frame));
        }
    }
}


void grey_scale::process()    
{   
    proc_launcher(&grey_scale::grey_scale_process, processed_buffer);
    
    //out_buffer = processed_buffer;
}