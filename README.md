# C-Tuple
C Tuple is a simple set of functions and a struct that mirrors a basic Tuple type found in C++, C# and other multi-paradigm languages.

## Usage
Simply add the Tuple.h and Tuple.c files to your C or C++ project, or any other project that supports native/external function invokation.

Here is some sample code of Tuples in use, below. *Keep in mind that a Tuple holds an array of void pointers, rather than actually casted values. Thus, you must know the casted types of each void pointer, or rather the return signature of the function returning a Tuple, in order to cast to the proper values.*

```c
typedef struct TStruct {
	char* value;
} TestStruct;

// The documentation for a function that returns a Tuple should explicitly say what kinda of Tuple it returns.
// e.g.
// TestTupleA() returns a Tuple(int*, int*, char*).
// Statically Returns Tuple(int*->5129, int*->999182, char*->"Hello, World!")
Tuple* TestTupleA() {
	// Create a pointer to each value you want the Tuple to return a void* to,
	// then pass it into the Tuple.
	int* a = (int*)malloc(sizeof(int));
	int* b = (int*)malloc(sizeof(int));
	*a = 5129;
	*b = 999182;
	char* c = "Hello, World!";
	return CreateTuple(3, a, b, c);
}

// TestTupleB returns a Tuple(char*, int*, float*, long long int*, char*, TestStruct*)
// Statically Returns Tuple(char*->'a', int*->(-52), float*->5.1, long long int*=-5291828747, char*->"lol, you!", TestStruct*->TestStruct("some value"))
Tuple* TestTupleB() {
	// Same deal with the pointers, but theres alot more here.
	char* a = (char*)malloc(sizeof(char));
	int* b = (int*)malloc(sizeof(int));
	float* c = (float*)malloc(sizeof(float));
	long long int* d = (long long int*)malloc(sizeof(long long int));
	TestStruct* f = (TestStruct*)malloc(sizeof(TestStruct));

	*a = 'a';
	*b = -52;
	*c = 5.1;
	*d = -5291828747;
	char* e = "lol, you!";
	f->value = "some value";
	
	return CreateTuple(6, a, b, c, d, e, f);
}

// This is an example of getting all the values from the void** values found in a Tuple
int main() {
	// We expect three return variables from tuple since the docs for TestTupleA say so;
	// Thus we can assume that tuple has only three params in values;
	// However, we will ensure this is correct using tSize.
	Tuple* tuple = TestTupleA();
	
	if (tuple->tSize != 3) { // TestTupleA() didn't return a value with three return values, like it said it would!
		printf("TestTupleA did not return a value with the expected number of values.");
	}
	else {
		int a = *((int*)tuple->values[0]);
		int b = *((int*)tuple->values[1]);
		char* c = (char*)tuple->values[2];
		
		printf("a = %i \nb = %i \nc = %s", a, b, c);
		// Prints:
		//	a = 5129
		//	b = 999182
		//	c = Hello, World!
	}
	
	// TestTupleB states that it returns 6 values
	// of types char*, int*, float*, long long int*, char* and TestStruct*
	tuple = TestTupleB();
	
	if (tuple->tSize != 6) {
		printf("TestTupleB did not return a value with the expected number of values.");
	}
	else {
		char* a = (char*)tuple->values[0];
		int b = *((int*)tuple->values[1]);
		float c = *((float*)tuple->values[2]);
		long long int d = *((long long int*)tuple->values[3]);
		char* e = (char*)tuple->values[4];
		TestStruct* f = (TestStruct*)tuple->values[5];
		
		printf("a = %s \nb = %i \nc = %f \nd = %lli \ne = %s \nf->value = %s", a, b, c, d, e, f->value);
		// Prints:
		//	a = 'a'
		//	b = -52
		//	c = 5.1
		//	d = -5291828747
		//	e = "lol, you!"
		//	f->value = "some value"
	}
	
	DestroyTuple(tuple); // Ensure that the memory is freed up after usage.

	return 0;
}
```

## Building A DLL

If you need a DLL for PInvoking it from C#, as an example, run the following commands over tuple.c

#### Windows (MinGW)
```bash
gcc -c -o tuple.o tuple.c -D TUPLE_EXPORTS
gcc -o tuple.dll tuple.o -s -shared -Wl,--subsystem,windows
```
#### OS X and Linux (GCC)
```bash
gcc -c tuple.c
gcc -shared -o tuple.dll tuple.o
```
