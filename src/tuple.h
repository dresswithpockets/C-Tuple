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

typedef struct s_tuple {
	int t_size;
	void** t_ptrs;
	int* t_stack;
} tuple;

typedef struct s_tuple_part {
	void* ptr;
	int on_stack;
} tuple_ptr;

TUPLEAPI tuple* TUPLECALL make_tuple(int, ...);
TUPLEAPI void TUPLECALL free_tuple(tuple*);

TUPLEAPI tuple_ptr* TUPLECALL tptr_stack(void*);
TUPLEAPI tuple_ptr* TUPLECALL tptr(void*);
TUPLEAPI void TUPLECALL free_tptr(tuple_ptr*);

#ifdef __cplusplus
}
#endif
