#include <stdio.h>
#include <stdlib.h>
#include "tuple.h"

tuple test_tuple() {
	
	// Create a value on the heap for use in tptr_owned(void* vptr)
	int* a = (int*)malloc(sizeof(int)); // Created on the heap
	*a = 5129;
	
	// Create a value on the stack for use in tptr_unowned(void* vptr)
	int b = 11111111;
	
	char* c = "Hello, World!";

	long long int* d = (long long int*)malloc(sizeof(long long int));
	*d = -5291828747;

	// Use tptr_owned for heap-allocated pointers and tptr_unowned for stack-allocated pointers.
	tuple t;
	make_tuple(&t, 4, tptr_owned(a), tptr_unowned(&b), tptr_unowned(c), tptr_owned(d));
	return t;
}

int main() {

	tuple t = test_tuple();

	// You have to cast to the pointer of the types return.
	// The intention of the returned values from a function that returns a tuple
	// should be defined by the documentation for that function.

	// some values may intend to return a pointer, others may intend to return a value.

	// In which case, dereference the pointer to get a value, otherwise keep the pointer.

	int a = *((int*)t.t_ptrs[0]); // Dereference
	int b = *((int*)t.t_ptrs[1]); // Dereference
	char* c = (char*)t.t_ptrs[2]; // Keep the pointer
	long long int d = *((long long int*)t.t_ptrs[3]); // Dereference

	printf("a = %i \nb = %i \nc = %s\nd = %lld\n", a, b, c, d);

	free_tuple(t);

	return 0;
}