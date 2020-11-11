#include "video_base.hpp"


// ############## PRIVATE METHODS ###########
template <typename T>
void video_base::init(T arg)
{
    try
    {
        cap.setExceptionMode(true);
        cap.open(arg);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    // Check if camera opened successfully
    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
    }
    int i = cap.get(cv::CAP_PROP_FRAME_COUNT );
    std::cout<< "Total frames "<< i << std::endl;
}

bool video_base::check_exit()
{
    // Press  ESC on keyboard to exit
    bool closing_controller{false};
    char c=(char)cv::waitKey(25);
    if(c==27)
        closing_controller = true;
    return closing_controller;
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

std::shared_ptr<FrameQueue<cv::Mat>> get_buffer()
{
    return std::make_shared<FrameQueue<cv::Mat>>();
}

void video_base::destroy_stream()
{
    std::scoped_lock lock(base_mutex);
    std::cout << "closing" << std::endl;
    // When everything done, release the video capture object
    cap.release();
    // Closes all the frames
    cv::destroyAllWindows();
    // Stop threads
    for (auto& thread : threads)
    {
        if (thread.joinable()) thread.join();
    }
}

// ############## PUBLIC METHODS ###########

void video_base::display()
{
    while (true)
    {
        std::scoped_lock lock(base_mutex);
        // Display the resulting frame
        if (!(*display_buffer).empty())
        {
            cv::imshow( "Frame", (*display_buffer).pop_front());
        } 
        if (check_exit())
            break;
    }
    destroy_stream();
}

void video_base::send(){/*todo*/}
