
#include "Tests.hpp"

int main() {

	test_enc_padding_0();
	test_enc_padding_1();
	test_enc_padding_2();

	test_enc_edge_case_1();
	test_enc_edge_case_0();
	test_enc_edge_case_2();

	test_dec_padding_0();
	test_dec_padding_1();
	test_dec_padding_2();

	test_dec_edge_case_1();
	test_dec_edge_case_2();

	test_dec_invalid();
	test_dec_empty();

	test_full();

	return 0;
}

