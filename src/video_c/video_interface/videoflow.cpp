#include "videoflow.hpp"

void videoflow::destroy_frames ()
{
    std::scoped_lock lock(m_mutex);
    // Closes all the frames
    cv::destroyAllWindows();
    bool test1 = (*m_capture_ptr).isOpened();
    // When everything done, release the video capture object
    (*m_capture_ptr).release();
    // Stop threads
    bool test2 = (*m_capture_ptr).isOpened();
    for (auto& thread : m_threads)
    {
        std::cout<<"stopping threads"<<std::endl;
        if (thread.joinable()) thread.join();
    }            
}

void videoflow::init_methods(video_instance *p_video_instance)
{
    m_capture_ptr = p_video_instance->capture_ptr;
    p_grey_scale = new grey_scale(p_video_instance);
    p_load_frames = new load_frames(p_video_instance);
    p_blurr_frames = new blurr(p_video_instance);
    p_canny_frames = new canny(p_video_instance);
    p_display_frames = new display_frames(p_video_instance);
}

void videoflow::destroy_stream()
{
    destroy_frames();
}

videoflow::videoflow(std::string &filename) : m_filename{filename} 
{
    p_video_instance = video_instance::get_instance(m_filename);
    init_methods(p_video_instance);        
}

videoflow::videoflow(int &device) : m_device{device} 
{
    p_video_instance = video_instance::get_instance(m_device);
    init_methods(p_video_instance);    
}

void videoflow::proc_launcher(process_interface *proc_ptr,
                                        std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                                        std::shared_ptr<object_queue<cv::Mat>> buffer_in)
        {
            m_threads.push_back(std::thread(&process_interface::do_process, proc_ptr, buffer_out, buffer_in));
        }

std::shared_ptr<object_queue<cv::Mat>> videoflow::get_buffer()
        {
            return std::make_shared<object_queue<cv::Mat>>();
        }

void videoflow::display(std::shared_ptr<object_queue<cv::Mat>> buffer_out)
        {
            p_display_frames->do_process(buffer_out, nullptr);
            destroy_stream();
        }

void videoflow::send(std::shared_ptr<object_queue<cv::Mat>> buffer_out) 
        {

        }

videoflow::~videoflow() {}