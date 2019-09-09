#pragma once

#include "Base64.hpp"
#include <cassert>

void test_enc_padding_0() {
	std::vector<char> a = { '1', '2', '3' };
	assert(Base64::encode(a) == std::string("MTIz"));
}

void test_enc_padding_1() {
	std::vector<char> a = { '1', '2', '3', '4' };
	assert(Base64::encode(a) == std::string("MTIzNA=="));
}

void test_enc_padding_2() {
	std::vector<char> a = { '1', '2', '3', '4', '5' };
	assert(Base64::encode(a) == std::string("MTIzNDU="));
}

void test_enc_edge_case_0() {
	std::vector<char> a;
	assert(Base64::encode(a) == std::string(""));
}

void test_enc_edge_case_1() {
	std::vector<char> a = { 'A' };
	assert(Base64::encode(a) == std::string("QQ=="));
}


void test_enc_edge_case_2() {
	std::vector<char> a = { 'A', 'B' };
	assert(Base64::encode(a) == std::string("QUI="));
}

void test_dec_padding_0() {
	std::string a("MTIz");
	std::vector<char> b = { '1', '2', '3' };
	assert(Base64::decode(a) == b);
}

void test_dec_padding_1() {
	std::string a("MTIzNA==");
	std::vector<char> b = { '1', '2', '3', '4' };
	assert(Base64::decode(a) == b);
}

void test_dec_padding_2() {
	std::string a("MTIzNDU=");
	std::vector<char> b = { '1', '2', '3', '4', '5' };
	assert(Base64::decode(a) == b);
}

void test_dec_edge_case_1() {
	std::string a("QQ==");
	std::vector<char> b = { 'A' };
	assert(Base64::decode(a) == b);
}

void test_dec_edge_case_2() {
	std::string a("QUI=");
	std::vector<char> b = { 'A', 'B' };
	assert(Base64::decode(a) == b);
}

void test_dec_invalid() {
	std::string a("=");
	try {
		Base64::decode(a);
	}
	catch (Base64::InvalidInput& e) {
		assert(1);
		return;
	}
	assert(0);
}

void test_dec_empty() {
	std::string a("");
	std::vector<char> b;
	assert(Base64::decode(a) == b);
}

void test_full() {
	std::string a("TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc2NpbmcgZWxpdCwgc2VkIGRvIGVpdXNtb2QgdGVtcG9yIQ==");
	assert(Base64::encode(Base64::decode(a)) == a);
}

