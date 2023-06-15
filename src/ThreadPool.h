#pragma once

#include <atomic>
#include <functional>

#include "ThreadSafeQueue.h"

class ThreadPool
{
public:
	ThreadPool(int threadCount);
	~ThreadPool();

	template<typename FunctionType>
	inline void Submit(FunctionType func)
	{
		WorkQueue.Push(std::function<void()>(func));
	}

	void WaitTillDone();

private:
	void WorkerThread();

private:
	std::atomic_bool done;
	ThreadSafeQueue<std::function<void()>> WorkQueue;
	std::vector<std::jthread> threads;
};
