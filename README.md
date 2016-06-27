# C-Tuple
C Tuple is a simple set of functions and a struct that mirrors a basic Tuple type found in C++, C# and other multi-paradigm languages.

## Usuage
Simply add the Tuple.h and Tuple.c files to your C or C++ project, or any other project that supports native/external function invokation. You should beable to call CreateTable and DestroyTable freely.

If you need a DLL for PInvoking it from C#, as an example, run the following gcc commands over Tuple.c

```
gcc -c Tuple.c
gcc -shared -o Tuple.dll Tuple.o
```

And it should output a dll.
