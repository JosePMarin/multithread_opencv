#include "process_frame.hpp"

class video_interface : public process_frame
{
private:

    video_interface() = delete;     //Forbid default constructor

protected:

    video_interface(int device) : process_frame{device}{}

    video_interface(std::string &filename) : process_frame{filename}{}

public:
    
    virtual ~video_interface(){}

    virtual void process() = 0;
};