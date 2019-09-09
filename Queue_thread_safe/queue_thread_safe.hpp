#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace my {

template <typename T>
class Queue {

public:

	Queue();
	~Queue();

	Queue(Queue&& input);
	Queue(const Queue& input);

	void push(T&& data);
	T pop();
	T pop_wait();
	bool empty();

private:

	mutable std::mutex mtx;
	std::queue<T> container;
	std::condition_variable cv;

};

template<typename T>
Queue<T>::Queue() {
}

template<typename T>
Queue<T>::Queue(Queue&& input) {
	std::scoped_lock<std::mutex, std::mutex> sl(mtx, input.mtx);
	this->container = std::move(input.container);
}

template<typename T>
Queue<T>::Queue(const Queue& input) {
	std::scoped_lock<std::mutex, std::mutex> sl(mtx, input.mtx);
	this->container = input.container;
}

template<typename T>
Queue<T>::~Queue() {
}

template<typename T>
void Queue<T>::push(T&& data) {
	{
		std::scoped_lock<std::mutex> lock(mtx);
		container.push(std::forward<T>(data));
	}
	cv.notify_one();
}

template<typename T>
T Queue<T>::pop() {
	std::scoped_lock<std::mutex> lock(mtx);
	T first = container.front();
	container.pop();
	return first;
}

template<typename T>
T Queue<T>::pop_wait() {
	std::unique_lock<std::mutex> lock(mtx);
	while (container.empty()) {
		cv.wait(lock);
	}
	T first = container.front();
	container.pop();
	return first;
}

template<typename T>
bool Queue<T>::empty() {
	std::scoped_lock<std::mutex> lock(mtx);
	return container.empty();
}


}