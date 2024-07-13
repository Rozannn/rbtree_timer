#include <iostream>
#include <windows.h>
#include "rbt_timer.h"
void test_func(struct timer_node_s* tn) {
	std::cout << "hello world at "<< tn->node.key <<std::endl;
}

int main()
{
	init_timer();
	add_timer(1000, test_func);
	add_timer(2000, test_func);
	add_timer(3000, test_func);
	add_timer(4000, test_func);
	add_timer(5000, test_func);
	add_timer(6000, test_func);
	while (find_nearest()!=-1) {
		handle_timer();
	}
	return 0;
}
