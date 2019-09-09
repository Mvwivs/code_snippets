#include "Tests.hpp"

int main() {

	test_string_edge_case_1();
	test_string_edge_case_2();
	test_string();
	test_string_empty();
	test_w_string();
	test_u16_string();
	test_u32_string();
	test_C_string();
	test_C_string_empty();
	test_C_u16_string();
	test_C_array();
	test_nullptr();

	return 0;
}