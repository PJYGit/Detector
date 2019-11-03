/* 
	This file includes all the definition of the needed utiliy functions.
*/

#include <stdio.h>
// check if one processor with id is finished
int is_finished(int* A, int m, int id);
// check if the OS can allocate resource to the processor with id
int can_allocate(int* R, int* U, int m, int id);
// check if one processor can get the resource
int one_can_run(int* f, int* R, int* U, int m, int n);
// check if there is a deadlock
int is_deadlock(int* f, int m);
// init the T array
void init_T(int* T, int* U, int m);
// print all the processors id involved in the deadlock
void print_deadlock(int* f, int m);
// add the processor id to the target array
void add_proc(int* target, int id, int n);
// init the target array to all zeroes
void init_to_zero(int* target, int n);

