#pragma once
#include "process_frame/process_base.hpp"
#include "process_frame/blurr.hpp"
#include "process_frame/canny.hpp"
#include "process_frame/display.hpp"
#include "process_frame/grey_scale.hpp"
#include "process_frame/load_frames.hpp"

class videoflow
{
    private:

        int m_device;
        std::string m_filename;
        cv::VideoCapture *m_capture_ptr;
        std::vector<std::thread> m_threads;
        std::mutex m_mutex;
        public:
        process_base *p_process_base;
        process_interface *p_grey_scale;
        process_interface *p_load_frames;
        process_interface *p_blurr_frames;
        process_interface *p_canny_frames;
        process_interface *p_display_frames;

    private:

        void destroy_frames ();

        void init_methods(process_base *base);

        void destroy_stream();

    public:
        videoflow(std::string &filename);

        videoflow(int &device);

        void proc_launcher(process_interface *proc_ptr,
                                        std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                                        std::shared_ptr<object_queue<cv::Mat>> buffer_in);

        std::shared_ptr<object_queue<cv::Mat>> get_buffer();

        void display(std::shared_ptr<object_queue<cv::Mat>> buffer_out);

        void send(std::shared_ptr<object_queue<cv::Mat>> buffer_out);

        ~videoflow();
};