#include "video_interface/video_interface.hpp"

class slam : public video_interface
{
private:
    slam() = delete;
public:
    slam(int device) : video_interface{device}{}
    slam(std::string &filename) : video_interface{filename}{}
    void process();
    virtual ~slam() {}
};

void slam::process()
{
    load_buffer = video_base::get_buffer();
    proc_launcher(load_frames, load_buffer);
    display_buffer = load_buffer;
}

int main()
{
    std::string video = "test.mp4";
    slam instance = slam(video);
    instance.process();
    instance.display();
    return 0;
}