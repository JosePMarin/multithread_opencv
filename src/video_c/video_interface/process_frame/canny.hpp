#pragma once
#include "process_interface.hpp"


class canny : public process_interface
/** 
 * Object process that extracts contours (gradient between pixels) from 
 * frames. It take frames from buffer_in, process and move them to buffer_out
*/
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:
        void proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);
    public:
        canny(video_instance *p_video_instance);

        virtual void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);
        ~canny();
};