
#include "Base64.hpp"

const char* Base64::InvalidInput::what() const throw() {
	return "Input is invalid base64 string";
}

namespace {

/*	Encodes 6 bits into char	*/
static constexpr char _table[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

/*	Calculates base64 character's index	*/
char _find_value(char c) {
	if (c >= 'A' && c <= 'Z')
		return c - 'A';
	if (c >= 'a' && c <= 'z')
		return c - 71;
	if (c >= '0' && c <= '9')
		return c + 4;
	if (c == '+')
		return 62;
	if (c == '/')
		return 63;

	return char(65); // character isn't valid
}

bool _is_valid(const std::string& input) {
	if (input.size() % 4 != 0) {
		return false;
	}

	for (std::size_t i = 0; i < input.size() - 3; ++i) {
		if (_find_value(input[i]) == 65) {
			return false;
		}
	}

	std::size_t eq_pos = input.find('=', input.size() - 3);
	if (eq_pos == std::string::npos) {
		eq_pos = input.size();
	}
	for (std::size_t i = input.size() - 3; i < eq_pos; ++i) {
		if (_find_value(input[i]) == 65) {
			return false;
		}
	}
	for (std::size_t i = eq_pos; i < input.size(); ++i) {
		if (input[i] != '=') {
			return false;
		}
	}
	return true;
}

}

/*	Encodes input binary data into base64 form and returns it as a string	*/
std::string Base64::encode(const std::vector<char>& input) {
	std::string result;
	result.reserve(input.size() * 4 / 3 + 2);

	std::size_t i = 0;
	if (input.size() > 2) {
		for (; i < input.size() - 2; i += 3) {
			result.push_back(_table[input[i] >> 2]);
			result.push_back(_table[(((input[i] & 0x3) << 4) | ((input[i + 1] & 0xf0) >> 4))]);
			result.push_back(_table[(((input[i + 1] & 0xf) << 2) | ((input[i + 2] & 0xc0) >> 6))]);
			result.push_back(_table[input[i + 2] & 0x3f]);
		}
	}

	// Add padding
	if (i != input.size()) {
		result.push_back(_table[input[i] >> 2]);
		if ((i + 1) != input.size()) {
			result.push_back(_table[(((input[i] & 0x3) << 4) | ((input[i + 1] & 0xf0) >> 4))]);
			result.push_back(_table[(input[i + 1] & 0xF) << 2]);
		}
		else {
			result.push_back(_table[(input[i] & 0x3) << 4]);
			result.push_back('=');
		}
		result.push_back('=');
	}

	return result;
}


/*	Decodes base64 string into binary data	*/
std::vector<char> Base64::decode(const std::string& input) {

	if (input.empty()) {
		return std::vector<char>();
	}

	if (!_is_valid(input)) {
		throw Base64::InvalidInput();
	}
	std::vector<char> result;

	result.reserve(input.size() * 3 / 4 + 3);

	std::size_t size = input.size();
	if (input[input.size() - 1] == '=') {
		size -= 4;
	}

	std::size_t i = 0;
	for (; i < size; i += 4) {
		result.push_back((_find_value(input[i]) << 2) | ((_find_value(input[i + 1]) & 0x30) >> 4));
		result.push_back(((_find_value(input[i + 1]) & 0xf) << 4) | ((_find_value(input[i + 2]) & 0x3c) >> 2));
		result.push_back(((_find_value(input[i + 2]) & 0x3) << 6) | _find_value(input[i + 3]));
	}

	// Decode padding
	if (i != input.size()) {
		result.push_back((_find_value(input[i]) << 2) | ((_find_value(input[i + 1]) & 0x30) >> 4));
		if (input[input.size() - 2] != '=') {
			result.push_back(((_find_value(input[i + 1]) & 0xf) << 4) | ((_find_value(input[i + 2]) & 0x3c) >> 2));
		}
	}

	return result;
}


