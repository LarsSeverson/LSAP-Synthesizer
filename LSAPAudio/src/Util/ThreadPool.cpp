#include "audiopch.h"
#include "ThreadPool.h"
namespace LSAP {
	ThreadPool::ThreadPool(size_t numThreads) :
		stop(false)
	{
		for (size_t i = 0; i < numThreads; ++i) {
			threads.emplace_back([this] {
				while (true) {
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(mutex);
						condition.wait(lock, [this] { return stop || !tasks.empty(); });
						if (stop && tasks.empty()) {
							return;
						}
						task = std::move(tasks.front());
						tasks.pop();
					}
					task();
				}
				});
		}
	}
	ThreadPool::~ThreadPool()
	{
		{
			std::lock_guard<std::mutex> lock(mutex);
			stop = true;
		}
		condition.notify_all();
		for (auto& thread : threads) {
			thread.join();
		}
	}
}