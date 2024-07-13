#pragma once
#ifndef _marekr_rbtree_timer
#define _marekr_rbtree_timer
#include "ngx_rbtree.h"
#include <windows.h>
#include <assert.h>
struct timer_node_s;
typedef void (*timer_handler_ptr)(struct timer_node_s*);
struct timer_node_s {
	ngx_rbtree_node_t node;
	timer_handler_ptr handler;
};
typedef struct timer_node_s  timer_node_t;
unsigned int current_time();
void init_timer();
timer_node_t* add_timer(unsigned int expire, timer_handler_ptr func);
void delete_time(timer_node_t* tn);
void handle_timer();
int find_nearest();
#endif // !_marekr_rbtree_timer
