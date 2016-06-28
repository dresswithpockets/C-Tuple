# C-Tuple
C Tuple is a simple set of functions and a struct that mirrors a basic Tuple type found in C++, C# and other multi-paradigm languages.

## Usage
Simply add the Tuple.h and Tuple.c files to your C or C++ project, or any other project that supports native/external function invokation.

Here is some sample code of Tuples in use, below. *Keep in mind that a Tuple holds an array of void pointers, rather than actually casted values. Thus, you must know the casted types of each void pointer, or rather the return signature of the function returning a Tuple, in order to cast to the proper values.*

```c
#include <stdio.h>
#include <stdlib.h>
#include "tuple.h"

tuple* test_tuple() {
	
	// Create a value on the heap for use in tptr(void* vptr)
	int* a = (int*)malloc(sizeof(int)); // Created on the heap
	*a = 5129;
	
	// Create a value on the stack for use in tptr_stack(void* vptr)
	int b = 999182; 
	
	char* c = "Hello, World!";

	long long int* d = (long long int*)malloc(sizeof(long long int));
	*d = -5291828747;

	// Use tptr for heap-allocated pointers and tptr_stack for stack-allocated pointers.
	return make_tuple(4, tptr(a), tptr_stack(&b), tptr_stack(c), tptr(d));
}

int main() {

	tuple_debug(1);

	tuple* t = test_tuple();

	// You have to cast to the pointer of the types return.
	// The intention of the returned values from a function that returns a tuple
	// should be defined by the documentation for that function.

	// some values may intend to return a pointer, others may intend to return a value.

	// In which case, dereference the pointer to get a value, otherwise keep the pointer.

	int a = *((int*)t->t_ptrs[0]); // Dereference
	int b = *((int*)t->t_ptrs[1]); // Dereference
	char* c = (char*)t->t_ptrs[2]; // Keep the pointer
	long long int d = *((long long int*)t->t_ptrs[3]); // Dereference

	printf("a = %i \nb = %i \nc = %s\nd = %lld\n", a, b, c, d);

	free_tuple(t);

	log_allocations();

	return 0;
}
```

## Building A Shared Library

If you want to link to an SO instead of the .c files, do the thing:

```bash
gcc -std=c99 -c -Wall -Werror -fpic tuple.c
gcc -std=c99 -shared -o -tuple.so tuple.o
```
