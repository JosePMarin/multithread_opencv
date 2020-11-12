#include "display.hpp"

void display_frames::proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in)
{
    while ((*m_capture_ptr).isOpened())
    {
        std::scoped_lock lock(m_mutex);
        // Display the resulting frame
        if (!(*buffer_out).empty())
        {
            cv::imshow( "Frame", (*buffer_out).pop_front());
        } 
        if (check_exit())
            break;
    }
}

bool display_frames::check_exit()
{
    // Press  ESC on keyboard to exit
    bool closing_controller{false};
    char c=(char)cv::waitKey(25);
    if(c==27)
        closing_controller = true;
    return closing_controller;
}

display_frames::display_frames(process_base *base_ptr)
{
    m_capture_ptr = base_ptr->capture_ptr;
}

void display_frames::do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in)
{
    proc_init(buffer_out, buffer_in);
}

display_frames::~display_frames() {}