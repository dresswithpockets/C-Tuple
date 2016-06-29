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
#	ifdef TUPLE_EXPORTS
#		define TUPLEAPI __declspec(dllexport)
#	else
#		define TUPLEAPI __declspec(dllimport)
#	endif
#	define TUPLECALL __cdecl
#else
#	define TUPLEAPI
#	define TUPLECALL
#endif

#ifdef __cplusplus
extern "c" {
#endif

	/*! \file tuple.h
		\brief Tuple

		An implementation of Tuples in C-Lang using void pointers.
	*/

	/*! \def TUPLEAPI
		\brief Shorthand for __declspec(dllimport)
	*/

	/*! \def TUPLECALL
		\brief Shorthand for __cdecl
	*/

	/*!
		\brief A Tuple Representation. A value of values.

		A Tuple contains a collection of pointers to values,
		as well as information for if specific values were allocated on the stack or not.

		If the flags for each t_ptr provided in t_stack are incorrectly assigned,
		memory leakage will occur.

		\sa make_tuple(), free_tuple()
	*/
	typedef struct tuple {
		int t_size; ///< The number of pointers allocated to the t_ptrs array.
		void** t_ptrs; ///< A collection of generic pointers, each pointer pointing to a value of any type.
		int* t_stack; ///< A collection of flags identifying whether or not a ptr on t_ptrs of the same index has been allocated on the stack.
	} tuple;

	/*!
		\brief A Part of a Tuple.

		A Tuple Pointer or a Tuple Part is a value that contains a pointer to a value
		and a flag suggesting whether or not the value was allocated on the stack.

		If the on_stack flag is incorrectly applied, then memory leakage will occur.

		\sa tptr_owned(), tptr_unowned(), free_tptr()
	*/
	typedef struct tuple_ptr {
		void* ptr; ///< A pointer to a value of any type.
		int on_stack; ///< A flagg identifying whether or not the value assigned to ptr has been allocated on the stack.
	} tuple_ptr;

	/*! \fn int make_tuple(tuple* t, int n_args, ...)
		\brief Pass a collection of tuple_ptr to create a collection of any-value pointers.

		Ownership of the ptrs within tuple_ptrs is passed onto tuple* t.

		\param[out] t A pointer to an instance of tuple that is initialized on the stack.
		\param[in] n_args The number of arguments in the variable argument collection,
		\param[in] ... The collection of tuple_ptr pointers, preferrably created via tptr_owned(void* ptr) or tptr_unowned(void* ptr).
		\return 0 if there is an error when allocating for the tuple, 1 otherwise.

		\sa tptr_owned(), tptr_unowned(), free_tuple()
	*/
	TUPLEAPI int TUPLECALL make_tuple(tuple* t, int n_args, ...);

	/*!	\fn void free_tuple(tuple t)
		\brief Pass a pointer to a tuple to be correctly freed and deallocated.

		Values in the tuple that have an associated flag identifying it as a stack-allocated value will be ignored when freeing tuple's via free_tuple().

		\param t A pointer to an allocated tuple.
		\sa make_tuple()
	*/
	TUPLEAPI void TUPLECALL free_tuple(tuple t);

	/*!	\fn tuple_ptr* tptr_unowned(void* ptr)
		\brief Pass STACK ALLOCATED pointers to create a tuple_ptr*.

		\param ptr A pointer to any value that was allocated on the stack.
		\return A tuple_ptr* with a void* ptr assigned to the value passed through vptr, with the on_stack flag set to true.
		\sa tptr_owned(), free_tptr_ptr(), make_tuple()
	*/
	TUPLEAPI tuple_ptr TUPLECALL tptr_unowned(void* ptr);

	/*!	\fn tuple_ptr* tptr_owned(void* ptr)
		\brief Pass HEAP ALLOCATED pointers to create a tuple_ptr*.

		\param ptr A pointer to any value that was allocated on the heap.
		\return A tuple_ptr* with a void* ptr assigned to the value passed through vptr, with the on_stack flag set to false.
		\sa tptr_unowned(), free_tptr_ptr(), make_tuple()
	*/
	TUPLEAPI tuple_ptr TUPLECALL tptr_owned(void* ptr);

#ifdef __cplusplus
}
#endif