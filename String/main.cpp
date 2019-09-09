
#include "Tests.hpp"

int main() {
	test_c_str();
	test_c_str_empty();

	test_size();
	test_size_empty();

	test_compare_same();
	test_compare_diff();
	test_compare_empty();

	test_copy();
	test_move();

	test_assign_copy();
	test_assign_move();

	test_access_first();
	test_access_last();
	test_access_modify_first();
	test_access_modify_last();

	test_resize();
	test_push_back(); 
	test_swap();


	return 0;
}