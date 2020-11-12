#pragma once
#include "process_interface.hpp"

class load_frames : public process_interface
{
    private:
        cv::VideoCapture *m_capture_ptr;
        std::mutex m_mutex;
    private:
        void proc_init (std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);

    public:
        load_frames(process_base *base_ptr);

        void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);

        ~load_frames();
};