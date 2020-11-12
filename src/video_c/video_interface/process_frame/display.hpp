#pragma once
#include "process_interface.hpp"


class display_frames : public process_interface
/** 
 * Object process that displays the images from buffer_out. Check 
 * video for ESC key to be pressed to break process. buffer_in should
 * be passed as nullptr
*/
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:

        void proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);
        bool check_exit();
    public:

        display_frames(video_instance *p_video_instance);

        virtual void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);

        ~display_frames();
};