#include "video_instance.hpp"

class process_interface
{
public:
    std::vector<std::thread> threads;

public:
    virtual ~process_interface() {}

    virtual void do_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                                std::shared_ptr<FrameQueue<cv::Mat>> buffer_in) = 0;
};


class process_base 
{
    private:
        int m_device;
        std::string m_filename;
        video_base *m_base_ptr;
    public:
        cv::VideoCapture *capture_ptr;

    public:

        process_base(std::string &filename) : m_filename{filename} 
        {
            auto shared_video_instance = video_instance::get_instance(m_filename);
            m_base_ptr = shared_video_instance->base_ptr;
            capture_ptr = m_base_ptr->get_capture();
        }
        process_base(int device) : m_device{device}
        {
            auto shared_video_instance = video_instance::get_instance(m_device);
            m_base_ptr = shared_video_instance->base_ptr;
            capture_ptr = m_base_ptr->get_capture();
        }

        ~process_base(){}
};


class load_frames : public process_interface
{
    private:
        cv::VideoCapture *m_capture_ptr;
        std::mutex m_mutex;
    private:
        void proc_init (std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            cv::Mat frame;
            while((*m_capture_ptr).isOpened())
            {
                std::scoped_lock lock(m_mutex);
                // Capture frame-by-frame
                try
                {
                    (*m_capture_ptr).read(frame);
                    // If the frame is empty, break immediately
                    // otherwise load into buffer and notify
                    if (!frame.empty())
                    {
                        (*buffer_out).push_back(std::move(frame));
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

    public:
        load_frames(process_base *base_ptr)
        {
            m_capture_ptr = base_ptr->capture_ptr;
        }

        void do_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            proc_init(buffer_out, buffer_in);
        }

        ~load_frames() {}
};

class display_frames : public process_interface
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:

        void proc_init(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            while ((*m_capture_ptr).isOpened())
            {
                std::scoped_lock lock(m_mutex);
                // Display the resulting frame
                if (!(*buffer_out).empty())
                {
                    cv::imshow( "Frame", (*buffer_out).pop_front());
                } 
                if (check_exit())
                    break;
            }
        }
        bool check_exit()
        {
            // Press  ESC on keyboard to exit
            bool closing_controller{false};
            char c=(char)cv::waitKey(25);
            if(c==27)
                closing_controller = true;
            return closing_controller;
        }
    public:

        display_frames(process_base *base_ptr)
        {
            m_capture_ptr = base_ptr->capture_ptr;
        }

        virtual void do_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            proc_init(buffer_out, buffer_in);
        }

        ~display_frames() {}
};

class grey_scale : public process_interface
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:
        void proc_init(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            while (true)
            {
                std::scoped_lock lock(m_mutex);
                if ((*buffer_in).empty() && !(*m_capture_ptr).isOpened())
                    break;
                if (!(*buffer_in).empty()) 
                {
                    auto temp_frame = (*buffer_in).pop_front();
                    cv::cvtColor(temp_frame, temp_frame, cv::COLOR_BGR2GRAY);
                    (*buffer_out).push_back(std::move(temp_frame));
                }
            }
        }

    public:

        grey_scale(process_base *base_ptr)
        {
            m_capture_ptr = base_ptr->capture_ptr;
        }

        virtual void do_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            proc_init(buffer_out, buffer_in);
        }
        
        ~grey_scale() {}

};

class blurr : public process_interface
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:
        void proc_init(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            while (true)
            {
                std::scoped_lock lock(m_mutex);
                if ((*buffer_in).empty() && !(*m_capture_ptr).isOpened())
                    break;
                if (!(*buffer_in).empty()) 
                {
                    auto temp_frame = (*buffer_in).pop_front();
                    cv::GaussianBlur(temp_frame, temp_frame, cv::Size(7,7), 1.5, 1.5);
                    (*buffer_out).push_back(std::move(temp_frame));
                }
            }
        }
    public:
        blurr(process_base *base_ptr)
        {
            m_capture_ptr = base_ptr->capture_ptr;
        }

        virtual void do_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            proc_init(buffer_out, buffer_in);
        }
        ~blurr() {}
};

class canny : public process_interface
{
    private:
        std::mutex m_mutex;
        cv::VideoCapture *m_capture_ptr;
    private:
        void proc_init(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            while (true)
            {
                std::scoped_lock lock(m_mutex);
                if ((*buffer_in).empty() && !(*m_capture_ptr).isOpened())
                    break;
                if (!(*buffer_in).empty()) 
                {
                    auto temp_frame = (*buffer_in).pop_front();
                    cv::Canny(temp_frame, temp_frame, 0, 30, 3);
                    (*buffer_out).push_back(std::move(temp_frame));
                }
            }
        }
    public:
        canny(process_base *base_ptr)
        {
            m_capture_ptr = base_ptr->capture_ptr;
        }

        virtual void do_process(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                        std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
        {
            proc_init(buffer_out, buffer_in);
        }
        ~canny() {}
};

class videoflow
{
private:
    int m_device;
    std::string m_filename;
    cv::VideoCapture *m_capture_ptr;
    std::vector<std::thread> m_threads;
    std::mutex m_mutex;
public:
    process_base *p_process_base;
    process_interface *p_grey_scale;
    process_interface *p_load_frames;
    process_interface *p_blurr_frames;
    process_interface *p_canny_frames;
    process_interface *p_display_frames;
private:

    void destroy_frames ()
    {
        std::scoped_lock lock(m_mutex);
        // Closes all the frames
        cv::destroyAllWindows();
        bool test1 = (*m_capture_ptr).isOpened();
        // When everything done, release the video capture object
        (*m_capture_ptr).release();
        // Stop threads
        bool test2 = (*m_capture_ptr).isOpened();
        for (auto& thread : m_threads)
        {
            std::cout<<"stopping threads"<<std::endl;
            if (thread.joinable()) thread.join();
        }
        
        
        
    }
    void init_methods(process_base *base)
    {
        m_capture_ptr = base->capture_ptr;
        p_grey_scale = new grey_scale(base);
        p_load_frames = new load_frames(base);
        p_blurr_frames = new blurr(base);
        p_canny_frames = new canny(base);
        p_display_frames = new display_frames(base);
    }

    void destroy_stream()
    {
        destroy_frames();
    }

public:
    videoflow(std::string &filename) : m_filename{filename} 
    {
        p_process_base = new process_base(m_filename);
        init_methods(p_process_base);        
    }

    videoflow(int &device) : m_device{device} 
    {
        p_process_base = new process_base(m_device);
        init_methods(p_process_base);
    }
   
    void proc_launcher(process_interface *proc_ptr,
                                    std::shared_ptr<FrameQueue<cv::Mat>> buffer_out,
                                    std::shared_ptr<FrameQueue<cv::Mat>> buffer_in)
    {
        m_threads.push_back(std::thread(&process_interface::do_process, proc_ptr, buffer_out, buffer_in));
    }

    std::shared_ptr<FrameQueue<cv::Mat>> get_buffer()
    {
        return std::make_shared<FrameQueue<cv::Mat>>();
    }

    void display(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out)
    {
        p_display_frames->do_process(buffer_out, nullptr);
        destroy_stream();
    }

    void send(std::shared_ptr<FrameQueue<cv::Mat>> buffer_out) 
    {

    }

    ~videoflow() {}
};







