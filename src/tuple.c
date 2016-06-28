/*
C-Tuple - Tuple style generic types in C.
Copyright (c) 2016 Tristen Horton

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "tuple.h"

int debug_flag = 0;

int allocs = 0;
int frees = 0;

tuple* TUPLECALL make_tuple(int n_args, ...) {
	va_list varlist;
	va_start(varlist, n_args);

	int vars_size = 0;
	void** ptrs = (void**)malloc(n_args * sizeof(void*));
	if (debug_flag) printf("Allocated void pointer array at: %p for new tuple\n", ptrs);

	allocs++;

	int* stack = (int*)malloc(n_args * sizeof(int));
	if (debug_flag) printf("Allocated int array at: %p for new tuple\n", stack);

	allocs++;

	for (int i = 0; i < n_args; i++) {
		tuple_ptr* tptr = va_arg(varlist, tuple_ptr*);

		vars_size += sizeof(tptr);

		ptrs[i] = tptr->ptr;
		stack[i] = tptr->on_stack;

		if (debug_flag) printf("Freeing tuple_ptr pointer at: %p\n", tptr);
		free(tptr); // We want to free the pointer to the tuple_ptr but not the tuple_ptr's void pointer.

		frees++;
	}

	// Size of all of the arguments + size of an int value (vars_size) since tuple has an array of void* and a single int.
	tuple* t = (tuple*)malloc(vars_size + sizeof(vars_size) + sizeof(int*));
	if (debug_flag) printf("Allocated tuple pointer at: %p\n", t);

	allocs++;

	t->t_ptrs = ptrs;
	t->t_size = n_args;
	t->t_stack = stack;

	va_end(varlist);

	return t;
}

void TUPLECALL free_tuple(tuple* t) {
	for (int i = 0; i < t->t_size; i++) {
		if (!t->t_stack[i]) {
			if (debug_flag) printf("Freeing heap-pointer at: %p ... found in tuple: %p\n", t->t_ptrs[i], t);
			free(t->t_ptrs[i]);

			frees++;
		}
		else if (debug_flag) printf("Couldn't free stack-pointer at: %p ... found in tuple_ptr: %p\n", t->t_ptrs[i], t);
	}
	
	if (debug_flag) printf("Freeing void pointer array at: %p ... found in tuple: %p\n", t->t_ptrs, t);
	free(t->t_ptrs);

	frees++;

	if (debug_flag) printf("Freeing int array at: %p ... found in tuple: %p\n", t->t_stack, t);
	free(t->t_stack);

	frees++;
	
	if (debug_flag) printf("Freeing tuple: %p\n", t);
	free(t);

	frees++;
}

tuple_ptr* TUPLECALL tptr_stack(void* vptr) {
	tuple_ptr* tptr = (tuple_ptr*)malloc(sizeof(tuple_ptr));
	if (debug_flag) printf("Allocated tuple_ptr pointer at: %p ... contains a stack-pointer to: %p\n", tptr, vptr);

	allocs++;

	tptr->ptr = vptr;
	tptr->on_stack = 1;
	return tptr;
}

tuple_ptr* TUPLECALL tptr(void* vptr) {
	tuple_ptr* tptr = (tuple_ptr*)malloc(sizeof(tuple_ptr));
	if (debug_flag) printf("Allocated tuple_ptr pointer at: %p ... contains a heap-pointer to: %p\n", tptr, vptr);

	allocs++;

	tptr->ptr = vptr;
	tptr->on_stack = 0;
	return tptr;
}

void TUPLECALL free_tptr(tuple_ptr* tptr) {
	if (!tptr->on_stack) {
		if (debug_flag) printf("Freeing heap-pointer at: %p ... found in tuple_ptr: %p\n", tptr->ptr, tptr);
		free(tptr->ptr);

		frees++;
	}
	else {
		if (debug_flag) printf("Couldn't free stack-pointer at: %p ... found in tuple_ptr: %p\n", tptr->ptr, tptr);
	}

	if (debug_flag) { printf("Freeing tuple_ptr at: %p\n", tptr); }
	free(tptr);

	frees++;
}

void TUPLECALL tuple_debug(int debug) {
	debug_flag = debug;
}

void TUPLECALL log_allocations() {
	printf("\n\nALLOCATIONS: %i\nFREES: %i\n\n", allocs, frees);
}