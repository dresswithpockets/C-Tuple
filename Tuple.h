// Tuple.h

typedef struct STuple {
	int tSize;
	void** values;
} Tuple;

Tuple* CreateTuple(int, ...);
void DestroyTuple(Tuple*);