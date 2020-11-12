#pragma once
#include "video_instance.hpp"
#include "process_frame/blurr.hpp"
#include "process_frame/canny.hpp"
#include "process_frame/display.hpp"
#include "process_frame/grey_scale.hpp"
#include "process_frame/load_frames.hpp"

class videoflow
/**
 * Front library of the framework that provides a toolset for image processing.
 * it has instance of all the processes and a thread launcher for them to be 
 * in a multithread mode.
*/
{
    private:

        int m_device;
        std::string m_filename;
        cv::VideoCapture *m_capture_ptr;
        std::vector<std::thread> m_threads;
        std::mutex m_mutex;

    public:
    
        video_instance *p_video_instance;
        process_interface *p_grey_scale;
        process_interface *p_load_frames;
        process_interface *p_blurr_frames;
        process_interface *p_canny_frames;
        process_interface *p_display_frames;

    private:

        void destroy_frames ();

        void init_methods(video_instance *p_video_instance);

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