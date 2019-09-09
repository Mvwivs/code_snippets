#pragma once

#include <string>
#include <vector>
#include <exception>

/*	Base64 encoder/decoder.	*/
namespace Base64 {

	std::string encode(const std::vector<char>& input);
	std::vector<char> decode(const std::string& input);

	class InvalidInput : public std::exception {
	public:
		virtual const char* what() const throw();
	};

}

