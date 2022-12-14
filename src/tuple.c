/*
    Copyright 2022 Ashley Horton

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <stdarg.h>
#include <stdlib.h>
#include "tuple.h"

int TUPLECALL make_tuple(tuple* t, int n_args, ...) {

	va_list varlist;
	va_start(varlist, n_args);

	void** ptrs = (void**)malloc(n_args * sizeof(void*));
	if (ptrs == NULL) return 0;

	int* stack = (int*)malloc(n_args * sizeof(int));
	if (stack == NULL) return 0;

	for (int i = 0; i < n_args; i++) {
		tuple_ptr tptr = va_arg(varlist, tuple_ptr);

		ptrs[i] = tptr.ptr;
		stack[i] = tptr.on_stack;
	}

	t->t_size = n_args;
	t->t_ptrs = ptrs;
	t->t_stack = stack;

	va_end(varlist);

	return 1;
}

void TUPLECALL free_tuple(tuple t) {
	for (int i = 0; i < t.t_size; i++) {
		if (!t.t_stack[i]) free(t.t_ptrs[i]);
		t.t_ptrs[i] = 0;
	}

	free(t.t_ptrs);
	t.t_ptrs = 0;

	free(t.t_stack);
	t.t_stack = 0;
}

tuple_ptr TUPLECALL tptr_unowned(void* ptr) {
	tuple_ptr tptr;
	tptr.ptr = ptr;
	tptr.on_stack = 1;
	return tptr;
}

tuple_ptr TUPLECALL tptr_owned(void* ptr) {
	tuple_ptr tptr;
	tptr.ptr = ptr;
	tptr.on_stack = 0;
	return tptr;
}
