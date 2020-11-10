#include "video_base/video_base.hpp"

class grey_scale : public video_base
{
private:
    grey_scale() = delete;     //Forbid default constructor
protected:
    void grey_scale_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer);
    std::shared_ptr<FrameQueue<cv::Mat>> processed_buffer;
public:

    grey_scale(int device);
    
    grey_scale(std::string &filename);

    ~grey_scale() {}

    void process();
};


