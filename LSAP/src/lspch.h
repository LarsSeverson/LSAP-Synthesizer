#pragma once
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

//#include "LSAP/Log.h"
#define NOMINMAX
#ifdef LS_PLATFORM_WINDOWS
#include <Windows.h>
#endif