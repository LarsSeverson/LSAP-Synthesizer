#pragma once

#pragma comment(lib, "winmm.lib")

#define NOMINMAX

#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <vector>
#include <utility>
#include <string>

#ifdef LS_PLATFORM_WINDOWS
#include <Windows.h>
#endif