# C-Tuple
C Tuple is a simple set of functions and a struct that mirrors a basic Tuple type found in C++, C# and other multi-paradigm languages.

## Usuage
Simply add the Tuple.h and Tuple.c files to your C or C++ project, or any other project that supports native/external function invokation. You should beable to call CreateTable and DestroyTable freely.

If you need a DLL for PInvoking it from C#, as an example, run the following commands over tuple.c

#### Windows (MinGW)
```
gcc -c -o tuple.o tuple.c -D TUPLE_EXPORTS
gcc -o tuple.dll tuple.o -s -shared -Wl,--subsystem,windows
```
#### OS X and Linux (GCC)
```
gcc -c tuple.c
gcc -shared -o tuple.dll tuple.o
```
