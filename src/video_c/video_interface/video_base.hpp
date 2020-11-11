#pragma once

#include "common.hpp"

class video_base
{
private:
    std::experimental::filesystem::path m_pwd;
    std::string m_path;
    int m_device;
    
protected:
    std::vector <std::thread> threads;
    cv::VideoCapture cap;
    std::shared_ptr<FrameQueue<cv::Mat>> load_buffer;
	std::shared_ptr<FrameQueue<cv::Mat>>  display_buffer;
    std::mutex base_mutex;

private:
    
    video_base() = delete;     //Forbid default constructor

    template <typename T> 
    void init(T arg);
    
    bool check_exit(); 

protected:

    video_base(int device);
    
    video_base(std::string &filename);

    void destroy_stream();

    std::shared_ptr<FrameQueue<cv::Mat>> get_buffer(); 


public:

    virtual ~video_base() {}

    void display();

    void send();
};
