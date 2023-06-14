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

void ThreadPool::WorkerThread()
{
}
