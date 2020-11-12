#pragma once
#include "process_base.hpp"

class process_interface
{
public:
    std::vector<std::thread> threads;

public:
    virtual ~process_interface() {}

    virtual void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                                std::shared_ptr<object_queue<cv::Mat>> buffer_in) = 0;
};