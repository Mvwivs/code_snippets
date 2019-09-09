#pragma once

#include <cassert>
#include <thread>
#include <future>

#include "queue_thread_safe.hpp"

void test_empty() {
	my::Queue<int> a;
	assert(a.empty());
}

void test_not_empty() {
	my::Queue<int> a;
	a.push(1);
	assert(!a.empty());
}

void test_push_pop() {
	my::Queue<int> a;
	a.push(2);
	assert(a.pop() == 2);
}

void test_ctor() {
	my::Queue<int> a;
	a.push(2);
	my::Queue<int> b(a);
	assert(a.pop() == b.pop());
}

void test_ctor_move() {
	my::Queue<int> a;
	a.push(2);
	my::Queue<int> b(std::move(a));
	assert(b.pop() == 2);
}

void test_pop_wait() {
	my::Queue<int> a;
	auto first = std::async(&my::Queue<int>::pop_wait, &a);
	std::thread second(&my::Queue<int>::push, &a, 2);

	int res = first.get();
	second.join();
	assert(res == 2);
}