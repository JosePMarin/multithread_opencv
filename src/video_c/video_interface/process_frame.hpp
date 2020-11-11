#include "video_base.hpp"

class process_frame : public video_base
{
private:
    std::vector<std::shared_ptr<FrameQueue<cv::Mat>>> m_processes;

private:

    process_frame() = delete;     //Forbid default constructor

protected:

    process_frame(int device);
    
    process_frame(std::string &filename);

    template <typename T>
    void proc_launcher(T proc, std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in = nullptr);

    void load_frames (std::shared_ptr<FrameQueue<cv::Mat>> buffer_out);

    void pre_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out, std::shared_ptr<FrameQueue<cv::Mat>> buffer_in);

    void canny_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out, std::shared_ptr<FrameQueue<cv::Mat>> buffer_in);

    
public:

    virtual ~process_frame() {}

};


