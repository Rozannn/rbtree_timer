#include "rbt_timer.h"

ngx_rbtree_t timer;
static ngx_rbtree_node_t sentinel;

unsigned int current_time() {
	unsigned int time;
	LARGE_INTEGER system_time;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&system_time);
	time = (unsigned int)((system_time.QuadPart * 1000) / frequency.QuadPart);
	return time;
}

void init_timer() {
	ngx_rbtree_init(&timer, &sentinel, ngx_rbtree_insert_timer_value);
}

timer_node_t* add_timer(unsigned int expire, timer_handler_ptr func) {
	timer_node_t* tn = (timer_node_t*)malloc(sizeof(timer_node_t));
	assert(tn != NULL);
	tn->node.key = expire + current_time();
	tn->handler = func;
	ngx_rbtree_insert(&timer, &tn->node);
	return tn;
}

void delete_time(timer_node_t* tn) {
	ngx_rbtree_delete(&timer, &tn->node);
}

void handle_timer() {
	ngx_rbtree_node_t* root, * node;
	while (1) {
		root = timer.root;
		if (root == timer.sentinel) break;
		node = ngx_rbtree_min(root, timer.sentinel);
		if (node->key > current_time()) break;
		timer_node_t* tn = (timer_node_t*)(char*)node;
		tn->handler(tn);
		ngx_rbtree_delete(&timer, &tn->node);
	}
}

int find_nearest() {
	if (timer.root == timer.sentinel) return -1;
	ngx_rbtree_node_t* node;
	node = ngx_rbtree_min(timer.root, timer.sentinel);
	int diff = node->key - current_time();
	return diff > 0 ? diff : 0;
}