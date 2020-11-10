#pragma once

#include "common.hpp"

class video_base
{
private:
    std::experimental::filesystem::path m_pwd;
    std::string m_path;
    int m_device;
    std::condition_variable cv_frames_loaded;
    std::vector <std::thread> m_threads;
protected:
    cv::VideoCapture cap;
    std::shared_ptr<FrameQueue<cv::Mat>> load_buffer;
	std::shared_ptr<FrameQueue<cv::Mat>>  out_buffer;
    std::mutex base_mutex;

private:
    
    video_base() = delete;     //Forbid default constructor

    template <typename T> 
    void init(T arg);
    
    bool check_exit();

    

protected:

    void load_frames (std::shared_ptr<FrameQueue<cv::Mat>> buffer);

    virtual void process()=0; // abstract method

    void destroy_stream();

    template <typename T>
    void proc_launcher(T proc, std::shared_ptr<FrameQueue<cv::Mat>> buffer);

    video_base(int device);
    
    video_base(std::string &filename);

    

public:
    virtual ~video_base() {}

    void display();

    void send();
};
