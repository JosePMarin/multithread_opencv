#include "video_base.hpp"


// ############## PRIVATE METHODS ###########
template <typename T>
void video_base::init(T arg)
{
    try
    {
        m_cap.setExceptionMode(true);
        m_cap.open(arg);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    // Check if camera opened successfully
    if(!m_cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
    }
    int i = m_cap.get(cv::CAP_PROP_FRAME_COUNT );
    std::cout<< "Total frames "<< i << std::endl;
}

// ############## PROTECTED METHODS ###########

video_base::video_base(int device) : m_device(device)
{
    init(m_device);
}

video_base::video_base(std::string &filename)
{  
    m_pwd = std::experimental::filesystem::current_path();
    m_path = m_pwd.string() + "/src/video_c/videos/" + filename;
    std::cout << m_path << std::endl;
    init(m_path);
}

cv::VideoCapture *video_base::get_capture ()
{
    return &m_cap;
}






