#pragma once
#include "process_interface.hpp"

class load_frames : public process_interface
/** object that loads frames from capturevideo instance to buffer_out
 * buffer_in = MUST BE nullptr
 * **/
{
    private:
        cv::VideoCapture *m_capture_ptr;
        std::mutex m_mutex;
    private:
        void proc_init (std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);

    public:
        load_frames(video_instance *p_video_instance);

        void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);

        ~load_frames();
};