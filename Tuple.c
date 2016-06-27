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
#include "Tuple.h"

Tuple* CreateTuple(int n_args, ...) {
	va_list varlist;
	va_start(varlist, n_args);

	int varsSize;
	void** vars = (void**)malloc(n_args * sizeof(void*));

	for (int i = 0; i < n_args; i++) {
		void* arg = va_arg(varlist, void*);

		varsSize += sizeof(arg);

		vars[i] = arg;
	}

	// Size of all of the arguments + size of an int value (varsSize) since Tuple has an array of void* and a single int.
	Tuple* t = (Tuple*)malloc(varsSize + sizeof(varsSize));

	t->values = vars;
	t->tSize = n_args;

	va_end(varlist);

	return t;
}

void DestroyTuple(Tuple* t) {
	free(t->values);
	free(t);
}