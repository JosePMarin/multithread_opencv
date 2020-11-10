#include "video_c/video_base/video_base.hpp"
#include "video_c/grey_scale.hpp"

int main()
{
    std::string video = "test.mp4";
    grey_scale g_scale = grey_scale(video);
    g_scale.process();
    g_scale.display();
}