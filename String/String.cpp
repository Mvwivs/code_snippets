#include "String.hpp"

namespace my {

String::String() :
	size(0),
	reserved(1),
	data(std::make_unique<char[]>(1)) {
	data[0] = '\0';
}

String::String(const String& str) :
	size(str.size),
	reserved(0),
	data(nullptr) {

	if (str.data != nullptr) {
		allocate(size);
		copy_data(str);
	}

}

String::String(const char* c_str) :
	size(0),
	reserved(1),
	data(std::make_unique<char[]>(1)) {
	data[0] = '\0';
	if (c_str != nullptr) {
		if (c_str[0] != '\0') {
			std::size_t n = std::char_traits<char>::length(c_str);
			allocate(n + 1);
			std::char_traits<char>::copy(data.get(), c_str, n);
			size = n;
			data[size] = '\0';
		}
	}

}

String::String(String&& str) :
	size(std::move(str.size)),
	reserved(std::move(str.reserved)),
	data(std::move(str.data)) {
}

String::~String() {
}

String& String::operator=(const String& str) {
	if (this != &str) {
		String tmp(str);
		swap(tmp);
	}
	return *this;
}

String& String::operator=(String&& str) {
	if (this != &str) {
		size = std::move(str.size);
		reserved = std::move(str.reserved);
		data = std::move(str.data);
	}
	return *this;
}

bool String::operator==(const String& str) const {
	if (this == &str) {
		return true;
	}
	if (size != str.size) {
		return false;
	}
	for (std::size_t i = 0; i < size; ++i) {
		if (data[i] != str.data[i]) {
			return false;
		}
	}
	return true;
}

char String::operator[](std::size_t pos) const {
	return data[pos];
}

char& String::operator[](std::size_t pos) {
	return data[pos];
}

void String::reserve_space(std::size_t requested_size) {
	if (requested_size > reserved) {

		String tmp;
		tmp.allocate(requested_size);
		tmp.size = size;
		tmp.copy_data(*this);
		*this = std::move(tmp);

	}
}

const char * String::c_str() const {
	if (data == nullptr) {
		return "\0";
	}
	return data.get();
}

void String::swap(String& str) noexcept {
	std::swap(size, str.size);
	std::swap(reserved, str.reserved);
	std::swap(data, str.data);
}

void String::push_back(const char a) {

	if (reserved <= (size + 1)) {
		reserve_space(2 * (size + 1));
	}
	data[size] = a;
	++size;
	data[size] = '\0';


}

std::size_t String::get_size() const {
	return size;
}

std::size_t String::get_capacity() const {
	return reserved;
}

const char * String::get_data() const {
	return data.get();
}

void String::allocate(std::size_t requested_size) {
	if (requested_size > reserved) {
		data = std::make_unique<char[]>(requested_size);
		reserved = requested_size;

	}
}

/*	Copies data from input string to this*	*/
void String::copy_data(const String& str) {
	// VC++ doesn't allow copying with std::copy on unsafe pointers
	for (std::size_t i = 0; i < size; ++i) {
		data[i] = str.data[i];
	}
}



}