#pragma once

#include <memory>
#include <algorithm>

namespace my {


class String {
public:
	String();
	String(const String& str);
	String(const char* c_str);
	String(String&& str);
	~String();

	String& operator=(const String& str);
	String& operator=(String&& str);
	bool operator==(const String& str) const;
	char operator[](std::size_t pos) const;
	char& operator[](std::size_t pos);

	void reserve_space(std::size_t requested_size);
	const char* c_str() const;
	void swap(String& str) noexcept;
	void push_back(const char a);
	std::size_t get_size() const;
	std::size_t get_capacity() const;
	const char* get_data() const;

private:
	std::unique_ptr<char[]> data;
	std::size_t size;
	std::size_t reserved;

	void allocate(std::size_t requested_size);
	void copy_data(const String& str);

	

	/*	TODO:
	
	*/
};


}
