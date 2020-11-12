#pragma once
#include "process_interface.hpp"


class display_frames : public process_interface
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:

        void proc_init(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);
        bool check_exit();
    public:

        display_frames(process_base *base_ptr);

        virtual void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);

        ~display_frames();
};