#pragma once
#include "process_interface.hpp"

class grey_scale : public process_interface
/** 
 * Object process that applies black and white (turns from multichanel into 2 channel format).
 * loads images from buffer_in and moves processed ones to buffer_out
*/
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:
        void proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);

    public:

        grey_scale(video_instance *p_video_instance);

        virtual void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);
        
        ~grey_scale() {}

};