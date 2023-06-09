#include "ThreadPool.h"

ThreadPool::ThreadPool(int threadCount) : done(false)
{
	try 
	{
		for (int i = 0; i < threadCount; i++)
		{
			threads.push_back(std::jthread(&ThreadPool::WorkerThread, this));
		}
	}
	catch (...)
	{
		done = true;
		throw;
	}
}

ThreadPool::~ThreadPool()
{
	done = true;
}

void ThreadPool::WaitTillDone()
{
	while (!WorkQueue.IsEmpty()) {
		std::this_thread::yield();
	}

	done = true;

	for (auto& thread : threads) {
		thread.join();
	}
}

void ThreadPool::WorkerThread()
{
	while (!done)
	{
		std::function<void()> task;
		if (WorkQueue.TryPop(task))
		{
			task();
		}
		else
		{
			std::this_thread::yield();
		}
	}
}