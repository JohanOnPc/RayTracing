#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>

template<typename T>
class ThreadSafeQueue {
public:
	ThreadSafeQueue() {}

	void Push(T value);
	void WaitAndPop(T& value);
	std::shared_ptr<T> WaitAndPop();
	bool TryPop(T& value);
	std::shared_ptr<T> TryPop();
	bool IsEmpty() const;

private:
	mutable std::mutex mut;
	std::queue<T> dataQueue;
	std::condition_variable dataConditional;
};