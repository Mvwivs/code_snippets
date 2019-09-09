
#include "Tests.hpp"

int main() {

	test_empty();
	test_not_empty();
	test_push_pop();
	test_ctor();
	test_ctor_move();

	test_pop_wait();

	return 0;
}
