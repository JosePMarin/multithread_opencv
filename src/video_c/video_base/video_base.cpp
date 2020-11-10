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
    load_buffer = std::make_shared<FrameQueue<cv::Mat>>();
    proc_launcher(&video_base::load_frames, load_buffer);
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

void video_base::load_frames (std::shared_ptr<FrameQueue<cv::Mat>> buffer)
{
    cv::Mat frame;
    while(cap.isOpened())
    {
        std::scoped_lock lock(base_mutex);
        // Capture frame-by-frame
        try
        {
            cap.read(frame);
            // If the frame is empty, break immediately
            // otherwise load into buffer and notify
            if (!frame.empty())
            {
                (*buffer).push_back(std::move(frame));
            } else {
                break;
            }
        }
        catch(const cv::Exception& e)
        {
            std::cerr << e.what() << '\n';
            break;
        }
    }
}

// ############## PROTECTED METHODS ###########

video_base::video_base(int device=0) : m_device(device)
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

void video_base::destroy_stream()
{
    std::scoped_lock lock(base_mutex);
    std::cout << "closing" << std::endl;
    // When everything done, release the video capture object
    cap.release();
    // Closes all the frames
    cv::destroyAllWindows();
    // Stop threads
    for (auto& thread : m_threads)
    {
        if (thread.joinable()) thread.join();
    }
}

template <typename T>
void video_base::proc_launcher(T proc, std::shared_ptr<FrameQueue<cv::Mat>> buffer)
{
    m_threads.push_back(std::thread(proc, this, buffer));  
}

// ############## PUBLIC METHODS ###########

void video_base::display()
{
    while (true)
    {
        std::scoped_lock lock(base_mutex);
        // Display the resulting frame
        if (!(*out_buffer).empty())
        {
            cv::imshow( "Frame", (*out_buffer).pop_front());
        } 
        if (check_exit())
            break;
    }
    destroy_stream();
}

void video_base::send(){/*todo*/}
