#include "video_interface/videoflow.hpp"


class slam
{
private:
    
	std::shared_ptr<object_queue<cv::Mat>>  out_buffer;
    int m_device;
    std::string m_filename;
    videoflow *video;
private: 
    template <typename T>
    void init_instance(T arg)
    {
        video = new videoflow(arg);
    }

    void orb();

    cv::Mat intrinsic_matrix(double focus, int high, int width);
public:
    slam(int device);
    slam(std::string &filename);
    void process();
    ~slam() {}
};

slam::slam(int device) : m_device(device)
{
    init_instance(m_device);
}

slam::slam(std::string &filename) : m_filename(filename)
{
    init_instance(m_filename);
}

void slam::process()
{
    std::shared_ptr<object_queue<cv::Mat>> load_buffer = video->get_buffer();
    std::shared_ptr<object_queue<cv::Mat>> grey_buffer = video->get_buffer();
    std::shared_ptr<object_queue<cv::Mat>> blurr_buffer = video->get_buffer();
    std::shared_ptr<object_queue<cv::Mat>> canny_buffer = video->get_buffer();
    video->proc_launcher(video->p_load_frames, load_buffer, nullptr);   // load frames into buffer
    video->proc_launcher(video->p_grey_scale, grey_buffer, load_buffer);    // grey_scale frames
    video->proc_launcher(video->p_blurr_frames, blurr_buffer, grey_buffer);    // blurr frames
    video->proc_launcher(video->p_canny_frames, canny_buffer, blurr_buffer);    // blurr frames
    video->display(canny_buffer);   // display frames
    std::cout<<"endprocess"<<std::endl;   
}

cv::Mat slam::intrinsic_matrix(double focus, int high, int width)
{
    uchar mydata[]={1, 2, 1, 1, 2, 1, 1, 2, 1};
    cv::Mat mymat(3,3,CV_8UC1,mydata);

    /*
    1 2 1
    1 2 1
    1 2 1
    */
}

void slam::orb()
{
    // init ORB that is going to detect corners (keypoints)
    auto orb = cv::ORB::create();

    // Brute-Force matcher: matches between descriptors(vectors) of keypoints from each feature, using hamming distance
    auto bf = cv::BFMatcher::create(cv::NORM_HAMMING);
}


int main()
{
    std::string video_file  = "test.mp4";
    slam instance = slam(video_file);
    instance.process();
    return 0;
}