#pragma once
#include "video_instance.hpp"

class process_interface
/** Interface base for all the processes to apply the do_process method
 *  **/
{
public:
    virtual ~process_interface() {}

    virtual void do_process(std::shared_ptr<object_queue<cv::Mat>> buffer_out,
                                std::shared_ptr<object_queue<cv::Mat>> buffer_in) = 0;
};