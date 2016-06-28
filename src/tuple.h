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
#if _WIN32

#ifdef TUPLE_EXPORTS
#define TUPLEAPI __declspec(dllexport)
#else
#define TUPLEAPI __declspec(dllimport)
#endif

#define TUPLECALL __cdecl

#else

#define TUPLEAPI
#define TUPLECALL

#endif

#ifdef __cplusplus
extern "c" {
#endif

	/**
		A Tuple Representation.

		A value of values.
		A Tuple contains a collection of pointers to values,
		as well as information for if specific values were allocated on the stack or not.

		If the flags for each t_ptr provided in t_stack are incorrectly assigned,
		memory leakage will occur.
	*/
	typedef struct s_tuple {
		int t_size;
		void** t_ptrs;
		int* t_stack;
	} tuple;

	/**
		A Part of a Tuple.

		A Tuple Pointer or a Tuple Part is a value that contains a pointer to a value
		and a flag suggesting whether or not the value was allocated on the stack.

		If the on_stack flag is incorrectly applied, then memory leakage will occur.
	*/
	typedef struct s_tuple_part {
		void* ptr;
		int on_stack;
	} tuple_ptr;

	/**
		tuple* make_tuple(int n_args, ...)
		Pass a collection of tuple_ptr* in order to create a single tuple value that points to each value in the collection.

		@param n_args The number of arguments in the variable argument collection,
		@param ... The collection of tuple_ptr pointers, preferrably created via tptr(void* ptr) or tptr_stack(void* ptr).
		@see tptr(void* ptr)
		@see tptr_stack(void* ptr)
		@see free_tuple(tuple* t)

		@return A tuple pointer that contains a collection of pointers to values of any type.
	*/
	TUPLEAPI tuple* TUPLECALL make_tuple(int n_args, ...);

	/**
		void free_tuple(tuple* t)
		Pass a pointer to a tuple to be correctly freed and deallocated.
		Ptrs in the tuple that are on the stack will be ignored.

		@param t A pointer to an allocated tuple.
		@see make_tuple(int n_args, ...)
	*/
	TUPLEAPI void TUPLECALL free_tuple(tuple* t);

	/*
		tuple_ptr* tptr_stack(void* ptr)
		Pass STACK ALLOCATED pointers through tptr_stack(void*) to create a tuple_ptre* for make_tuple(int, ...)
		
		@param ptr A pointer to any value that was allocated on the stack.
		@see tptr(void* ptr)
		@see free_tptr(tuple_ptr* tptr)
		@see make_tuple(int n_args, ...)
		
		@return A tuple_ptr* with a void* ptr assigned to the value passed through the ptr param, and an on_stack flag.
	*/
	TUPLEAPI tuple_ptr* TUPLECALL tptr_stack(void* ptr);
	/**
		tuple_ptr* tptr(void* ptr)
		Pass HEAP ALLOCATED pointers through tptr(void*) to create a tuple_ptr* for make_tuple(int, ...)
		
		@param ptr A pointer to any value that was allocated on the heap.
		@see tptr_stack(void* ptr)
		@see free_tptr(tuple_ptr* tptr)
		@see make_tuple(int n_args, ...)

		@return A tuple_ptr* with a void* ptr assigned to the value passed through the ptr param, and no on_stack flag.
	*/
	TUPLEAPI tuple_ptr* TUPLECALL tptr(void* ptr);
	/**
		void free_tptr(tuple_ptr* tptr)
		Pass a tuple_ptr* to be correctly freed and deallocated. Stack-allocated values will be ignored.

		@param tptr A pointer to a tuple_ptr value to be deallocated, including the tptr->ptr value if the on_stack flag is false.
		@see tptr(void* ptr)
		@see tptr_stack(void* ptr)
	*/
	TUPLEAPI void TUPLECALL free_tptr(tuple_ptr* tptr);

#ifdef __cplusplus
}
#endif
