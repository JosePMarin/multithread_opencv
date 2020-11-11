#include "process_frame.hpp"


// ############## PROTECTED METHODS ###########
process_frame::process_frame(int device) : video_base{device}
{}
    
process_frame::process_frame(std::string &filename) : video_base{filename}
{}

template <typename T>
void process_frame::proc_launcher(T proc, std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                                std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
{
    if (buffer_in != nullptr)
        threads.push_back(std::thread(proc, this, buffer_out, buffer_in));
         
    threads.push_back(std::thread(proc, this, buffer_out));
}

void process_frame::load_frames (std::shared_ptr<FrameQueue<cv::Mat>> buffer_out)
{
    cv::Mat frame;
    while(cap.isOpened())
    {
        std::scoped_lock lock(base_mutex);
        // Capture frame-by-frame
        try
        {
            cap.read(frame);
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

void process_frame::pre_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out, std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
{
    while (true)
    {
        std::scoped_lock lock(base_mutex);
        if ((*buffer_in).empty() && !cap.isOpened())
            break;
        if (!(*buffer_in).empty()) 
        {
            auto temp_frame = (*buffer_in).pop_front();
            cv::cvtColor(temp_frame, temp_frame, cv::COLOR_BGR2GRAY);
            cv::GaussianBlur(temp_frame, temp_frame, cv::Size(7,7), 1.5, 1.5);
            (*buffer_out).push_back(std::move(temp_frame));
        }
    }
}

void process_frame::canny_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out, std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
{
    while (true)
    {
        std::scoped_lock lock(base_mutex);
        if ((*buffer_in).empty() && !cap.isOpened())
            break;
        if (!(*buffer_in).empty()) 
        {
            auto temp_frame = (*buffer_in).pop_front();
            cv::Canny(temp_frame, temp_frame, 0, 30, 3);
            (*buffer_out).push_back(std::move(temp_frame));
        }
    }
}
