#include "utils/common.hpp"

std::thread load_thread;
std::thread process_thread;
cv::VideoCapture cap;
bool closing_controller = false;
bool no_more_frames = false;
bool no_more_proc_frames = false;
std::mutex global_mutex;


std::chrono::_V2::system_clock::time_point check_time(std::chrono::_V2::system_clock::time_point *start=nullptr,
							std::chrono::_V2::system_clock::time_point *end=nullptr,
							const char *process=nullptr
							)
{
	std::chrono::_V2::system_clock::time_point time;
	if (start==nullptr && end == nullptr)
	{
		time = std::chrono::system_clock::now();
	} 
	if (process!=nullptr)
	{
		std::string str(process);
		std::chrono::duration<double> elapsed_seconds = *end-*start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(*end);

		std::cout << "finished "<< str << " at " << std::ctime(&end_time)
				<< "elapsed time: " << elapsed_seconds.count() << "s\n";
	}
	return time;
}


void destroy_stream()
{
	std::scoped_lock lock(global_mutex);
	std::cout<<"closing"<<std::endl;
	closing_controller = true;
	// When everything done, release the video capture object
	cap.release();

	// Closes all the frames
	cv::destroyAllWindows();

	// Destroy thread
	if (load_thread.joinable()) load_thread.join();
	if (process_thread.joinable()) process_thread.join();
}

bool check_exit()
{
	// Press  ESC on keyboard to exit
	char c=(char)cv::waitKey(25);
	if(c==27)
		closing_controller = true;
	return closing_controller;
}

void load_frames(cv::VideoCapture &cap, object_queue<cv::Mat> &load_buffer)
{
	auto before = check_time();
	cv::Mat frame;
	while(!closing_controller)
	{
		std::scoped_lock lock(global_mutex);
		cv::Mat frame;
		// Capture frame-by-frame
		try
		{
			if (cap.read(frame) == false)
				break;
			// If the frame is empty, break immediately
			if (!frame.empty())
			{
				load_buffer.push_back(std::move(frame));
			}
		}
		catch(const cv::Exception& e)
		{
			std::cerr << e.what() << '\n';
			no_more_frames = true;
			break;
		}
	}
	auto after = check_time();
	check_time(&before, &after, "load_frames");
}

void preProcFrame(object_queue<cv::Mat> &load_buffer, object_queue<cv::Mat> &out_buffer)    
{   
	auto before = check_time();
	while (!closing_controller)
	{
		std::scoped_lock lock(global_mutex);
		if (!load_buffer.empty())
		{
			auto temp_frame = load_buffer.pop_front();
			cv::cvtColor(temp_frame, temp_frame, cv::COLOR_BGR2GRAY);
			cv::GaussianBlur(temp_frame, temp_frame, cv::Size(7,7), 1.5, 1.5);
			cv::Canny(temp_frame, temp_frame, 0, 30, 3);
			out_buffer.push_back(std::move(temp_frame));

		} else if (no_more_frames){
			break;
		}
	}
	auto after = check_time();
	check_time(&before, &after, "process_frame");
}

void display(object_queue<cv::Mat> &out_buffer)
{
	auto before = check_time();	
	while (!closing_controller)
	{
		std::scoped_lock lock(global_mutex);
		// Display the resulting frame
		if (!out_buffer.empty())
		{
			cv::imshow( "Frame", out_buffer.pop_front());
		} else if (no_more_proc_frames) {
			break;
		} 
		check_exit();
	}
	auto after = check_time();
	check_time(&before, &after, "display");
}



int main(){

	// Create a VideoCapture object and open the input file
	// If the input is the web camera, pass 0 instead of the video file name
	std::experimental::filesystem::path current_path = std::experimental::filesystem::current_path();
	
	object_queue<cv::Mat> load_buffer;
	object_queue<cv::Mat> out_buffer;
	cv::Mat frame;
	

	cap.setExceptionMode(true);
	try
	{
		cap.open(current_path.string() + "/src/video_c/videos/test.mp4");
		int i = cap.get(cv::CAP_PROP_FRAME_COUNT );
		std::cout<< "Total frames "<< i << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	// Check if camera opened successfully
	if(!cap.isOpened()){
		std::cout << "Error opening video stream or file" << std::endl;
		return -1;
	}
	//load_frames(cap, load_buffer);
	//preProcFrame(load_buffer, out_buffer);

	load_thread = std::thread(load_frames, std::ref(cap), std::ref(load_buffer));
	process_thread = std::thread(preProcFrame, std::ref(load_buffer), std::ref(out_buffer));

	display(out_buffer);
	destroy_stream();
	return 0;
}