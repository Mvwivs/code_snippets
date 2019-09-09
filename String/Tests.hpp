#pragma once
#include <cstring>
#include <cassert>
#include "String.hpp"

void test_c_str() {
	my::String a("abc");
	assert(std::strcmp(a.c_str(), "abc") == 0);
}

void test_c_str_empty() {
	my::String a("");
	assert(std::strcmp(a.c_str(), "") == 0);
}

void test_size() {
	my::String a("abc");
	assert(a.get_size() == 3);
}

void test_size_empty() {
	my::String a;
	assert(a.get_size() == 0);
}

void test_compare_same() {
	my::String a("abc");
	my::String b("abc");
	assert(a == b);
}

void test_compare_diff() {
	my::String a("abc");
	my::String b("abb");
	assert(!(a == b));
}

void test_compare_empty() {
	my::String a("");
	my::String b("");
	assert(a == b);
}

void test_copy() {
	my::String a("ABC");
	my::String b(a);
	assert(a == b);
}

void test_move() {
	my::String a("ABC");
	my::String b("ABC");
	my::String c(std::move(b));
	assert(a == c);
}

void test_assign_copy() {
	my::String a("ABC");
	my::String b;
	my::String c;
	c = b = a;
	assert(a == b);
	assert(c == a);
}


void test_assign_move() {
	my::String a("ABC");
	my::String c("ABC");
	my::String b;
	b = std::move(a);
	assert(c == b);
}

void test_access_first() {
	my::String a("ABC");
	assert(a[0] == 'A');
}

void test_access_last() {
	my::String a("ABC");
	assert(a[a.get_size() - 1] == 'C');
}

void test_access_modify_first() {
	my::String a("ABC");
	a[0] = 'F';
	assert(a[0] == 'F');
}

void test_access_modify_last() {
	my::String a("ABC");
	a[a.get_size() - 1] = 'F';
	assert(a[a.get_size() - 1] == 'F');
}

void test_resize() {
	my::String a("ABC");
	my::String b(a);
	a.reserve_space(10);
	assert(a == b);
}

void test_push_back() {
	my::String a("ABC");
	a.push_back('F');
	assert(a[a.get_size() - 1] == 'F');
}

void test_swap() {
	my::String a("ABC");
	my::String b("xyz");
	my::String c(a);
	my::String d(b);
	c.swap(d);
	assert(a == d);
	assert(c == b);
}