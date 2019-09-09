#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace my {

template <typename Iter, typename CharT>
std::vector<std::basic_string<CharT> > split(Iter start, Iter end, CharT separator) {
	std::vector<std::basic_string<CharT> > res;

	//	for an empty input return empty string ""
	if (start == end) {
		res.emplace_back(std::basic_string<CharT>());
		return res;
	}

	Iter pos = std::find(start, end, separator);
	while (pos != end) {
		res.emplace_back(start, pos);
		start = pos + 1;
		pos = std::find(start, end, separator);
	}

	// Check for strings, that has separator as a last character
	if (start != end) {
		res.emplace_back(start, end);
	}
	return res;
}

// array with size string split function
template <typename CharT>
std::vector<std::basic_string<CharT> > split(const CharT* str, std::size_t length, CharT separator) {
	if (str == nullptr) {
		return std::vector<std::basic_string<CharT>>();
	}
	const CharT* start = str;
	const CharT* end = str + length;

	return split(start, end, separator);
}

// c++ std::basic_string<...> split function
template <typename CharT>
std::vector<std::basic_string<CharT> > split(const std::basic_string<CharT>& str, CharT separator) {
	auto start = str.begin();
	auto end = str.end();

	return split(start, end, separator);
}

// c style string split function
template <typename CharT>
std::vector<std::basic_string<CharT> > split(const CharT* str, CharT separator) {
	if (str ==  nullptr) {
		return std::vector<std::basic_string<CharT>>();
	}
	const CharT* start = str;
	const std::size_t length = std::char_traits<CharT>::length(str);
	const CharT* end = str + length;

	return split(start, end, separator);
}


}