#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <condition_variable>
#include <functional>
#include <experimental/filesystem>

#include "opencv2/opencv.hpp"

#include "object_queue.hpp"


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