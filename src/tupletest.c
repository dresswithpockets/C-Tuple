#include <stdio.h>
#include <stdlib.h>
#include "tuple.h"

typedef struct test {
	char* value;
} test;

tuple* test_tuple() {
	
	int* a = (int*)malloc(sizeof(int)); // Created on the heap
	*a = 5129;
	
	int b = 999182; // Created on the stack
	
	char* c = "Hello, World!"; // Created on the stack

	long long int* d = (long long int*)malloc(sizeof(long long int)); // Created on the heap
	*d = -5291828747;

	return make_tuple(4, tptr(a), tptr_stack(&b), tptr_stack(c), tptr(d));
}

int main() {

	tuple* t = test_tuple();

	int a = *((int*)t->t_ptrs[0]);
	int b = *((int*)t->t_ptrs[1]);
	char* c = (char*)t->t_ptrs[2];
	long long int d = *((long long int*)t->t_ptrs[3]);

	printf("a = %i \nb = %i \nc = %s\nd = %lld\n", a, b, c, d);

	free_tuple(t);

	return 0;
}