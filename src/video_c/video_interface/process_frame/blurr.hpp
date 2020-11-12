#pragma once
#include "process_interface.hpp"

class blurr : public process_interface
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:
        void proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);
    public:
        blurr(process_base *base_ptr);

        virtual void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);
        ~blurr();
};