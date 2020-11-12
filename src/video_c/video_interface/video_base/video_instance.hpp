#pragma once
#include "video_base.hpp"


class video_instance
/** 
 * Object singleton patterned that calls video_base just once and
 * returns this unique instance when called
*/
{
    private:
        static video_instance* m_instance;
        int m_device;
        std::string m_filename;
        video_base *m_base_ptr;
        

    public:
        cv::VideoCapture *capture_ptr;

    private:
        video_instance(int device);
        video_instance(std::string &filename);
    public:
        static video_instance* get_instance(int device);
        static video_instance* get_instance(std::string &filename);
        ~video_instance();
    };




