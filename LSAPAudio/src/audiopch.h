#pragma once

namespace Backend {
	static float sampleRate = 44100.0;
}

#define _USE_MATH_DEFINES
#define NOMINMAX
#include <Windows.h>

#include <iostream>
#include <memory>
#include <algorithm>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <tuple>
#include <unordered_map>
#include <map>
#include <future>
#include <cmath>
#include <math.h>
#include <type_traits>
#include <queue>
