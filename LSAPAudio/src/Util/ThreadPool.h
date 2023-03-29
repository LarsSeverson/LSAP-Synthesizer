#pragma once

namespace LSAP {
	class ThreadPool
	{
	public:
		ThreadPool(size_t numThreads);
		~ThreadPool();

		// Can pretty much take any function type with any amount of parameters and put it into the queue
		template<class F, typename ... Args>
		inline auto enQueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args ...>::type> {
			// For convenience we set a type "returnType" equal to whatever is the return of the f - function
			using returnType = typename std::invoke_result<F, Args...>::type;

			// Set the task = to the function as packaged and finally as a shared_ptr (it will need to move)
			auto task = std::make_shared<std::packaged_task<returnType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
			
			// Gather the return type which will be the future return of the packaged_task
			std::future<returnType> ret = task->get_future();

			{
				// Add the task to the queue
				std::lock_guard<std::mutex> lock(mutex);
				tasks.emplace([task] { return (*task)(); });
			}
			condition.notify_one();

			return ret;
		}

	private:
		std::vector<std::thread> threads;
		std::queue<std::function<void()>> tasks;
		std::mutex mutex;
		std::condition_variable condition;
		bool stop;
	};
}