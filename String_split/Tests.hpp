#pragma once

#include <string>
#include <vector>
#include <cassert>

#include "split.hpp"

void test_string_edge_case_1() {
	std::string a("");
	std::vector<std::string> b{ "" };
	assert(my::split(a, ' ') == b);
}

void test_string_edge_case_2() {
	std::string a("_");
	std::vector<std::string> b{ "" };
	assert(my::split(a, '_') == b);
}

void test_string() {
	std::string a("This is string");
	std::vector<std::string> b{ "This", "is", "string" };
	assert(my::split(a, ' ') == b);
}

void test_string_empty() {
	std::string a;
	std::vector<std::string> b{ "" };
	assert(my::split(a, '-') == b);
}

void test_w_string() {
	std::wstring a(L"W-STRING-testing");
	std::vector<std::wstring> b{ L"W", L"STRING", L"testing" };
	assert(my::split(a, L'-') == b);
}

void test_u16_string() {
	std::u16string a(u"U16_string_test");
	std::vector<std::u16string> b{ u"U16", u"string", u"test" };
	assert(my::split(a, u'_') == b);
}

void test_u32_string() {
	std::u32string a(U"U32_string_test");
	std::vector<std::u32string> b{ U"U32", U"string", U"test" };
	assert(my::split(a, U'_') == b);
}

void test_C_string() {
	const char* a = "This is C string ";
	std::vector<std::string> b{ "This", "is", "C", "string" };
	assert(my::split(a, ' ') == b);
}

void test_C_string_empty() {
	const char* a = "";
	std::vector<std::string> b{ "" };
	assert(my::split(a, ' ') == b);
}

void test_C_u16_string() {
	const char16_t* a = u"This is C u16string ";
	std::vector<std::u16string> b{ u"This", u"is", u"C", u"u16string" };
	assert(my::split(a, u' ') == b);
}

void test_C_array() {
	const std::size_t size = 12;
	const char a[size] = { 'C', ' ', 'A', 'r', 'r', 'a', 'y', ' ', 't', 'e', 's', 't' };
	std::vector<std::string> b{ "C", "Array", "test" };
	assert(my::split(a, size, ' ') == b);
}

void test_nullptr() {
	const char* a = nullptr;
	std::vector<std::string> b;
	assert(my::split(a, '-') == b);
}
