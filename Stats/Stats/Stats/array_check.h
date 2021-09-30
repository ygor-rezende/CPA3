/*!	file		array_check.h
	author		Ygor Lopez de Rezende
	date		2021-03-01

	Stats.c header file.
*/

// Windows Win32 API and later only (x86 & x64 supports this)
#if defined(_WIN32)		
#include <crtdbg.h>		// CRT = C-Runtime, DBG = debug
						// debug versions of the C-runtime
#endif


//global variable:
// holds the quantity of items in the list
size_t size;

char* getDynamicWord();
double* getDynamicArray();