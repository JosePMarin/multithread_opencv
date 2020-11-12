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
#include <opencv2/features2d.hpp>

#include "object_queue.hpp"
#include "custom_data.hpp"
