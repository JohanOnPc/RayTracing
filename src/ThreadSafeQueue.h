#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>

template<typename T>
class ThreadSafeQueue {
public:
	ThreadSafeQueue() {}

	inline void Push(T value)
	{
		std::lock_guard<std::mutex> lock(mut);
		dataQueue.push(std::move(value));
		dataConditional.notify_one();
	}

	inline void WaitAndPop(T& value)
	{
		std::unique_lock<std::mutex> lock(mut);
		dataConditional.wait(lock, [this] {return !dataQueue.empty(); });
		value = std::move(dataQueue.front());
		dataQueue.pop();
	}

	inline std::shared_ptr<T> WaitAndPop()
	{
		std::unique_lock<std::mutex> lock(mut);
		dataConditional.wait(lock, [this] {return !dataQueue.empty(); });
		std::shared_ptr<T> result(
			std::make_shared(std::move(dataQueue.front()))
		);
		dataQueue.pop();

		return result;
	}

	inline bool TryPop(T& value)
	{
		std::lock_guard<std::mutex> lock(mut);
		if (dataQueue.empty()) {
			return false;
		}

		value = std::move(dataQueue.front());
		dataQueue.pop();

		return true;
	}

	inline std::shared_ptr<T> TryPop()
	{
		std::lock_guard<std::mutex> lock(mut);
		if (dataQueue.empty()) {
			return std::shared_ptr<T>();
		}
		std::shared_ptr<T> result(
			std::make_shared<T>(std::move(dataQueue.front()))
		);
		dataQueue.pop();

		return result;
	}

	inline bool IsEmpty() const
	{
		std::lock_guard<std::mutex> lock(mut);
		return dataQueue.empty();
	}


private:
	mutable std::mutex mut;
	std::queue<T> dataQueue;
	std::condition_variable dataConditional;
};