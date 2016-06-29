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