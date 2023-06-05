#include "ThreadSafeQueue.h"

template<typename T>
inline void ThreadSafeQueue<T>::Push(T value)
{
	std::lock_guard<std::mutex> lock(mut);
	dataQueue.push(std::move(value));
	dataConditional.notify_one();
}

template<typename T>
inline void ThreadSafeQueue<T>::WaitAndPop(T& value)
{
	std::unique_lock<std::mutex> lock(mut);
	dataConditional.wait(lock, [this] {return !dataQueue.empty(); });
	value = std::move(dataQueue.front());
	dataQueue.pop();
}

template<typename T>
inline std::shared_ptr<T> ThreadSafeQueue<T>::WaitAndPop()
{
	std::unique_lock<std::mutex> lock(mut);
	dataConditional.wait(lock, [this] {return !dataQueue.empty(); });
	std::shared_ptr<T> result(
		std::make_shared(std::move(dataQueue.front()))
	);
	dataQueue.pop();

	return result;
}

template<typename T>
inline bool ThreadSafeQueue<T>::TryPop(T& value)
{
	std::lock_guard<std::mutex> lock(mut);
	if (dataQueue.empty()) {
		return false;
	}

	value = std::move(dataQueue.front());
	dataQueue.pop();

	return true;	
}

template<typename T>
inline std::shared_ptr<T> ThreadSafeQueue<T>::TryPop()
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

template<typename T>
inline bool ThreadSafeQueue<T>::IsEmpty() const
{
	std::lock_guard<std::mutex> lock(mut);
	return dataQueue.empty();
}