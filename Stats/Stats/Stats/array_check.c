/*!	file		array_check.c
	author		Ygor Lopez de Rezende
	date		2021-03-01
*/

#define _CRT_SECURE_NO_WARNINGS
#include "array_check.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(_WIN32)
#ifdef _M_X64
void* const DBG_PTR = (void* const)0xcccccccccccccccc;
#else
void* const DBG_PTR = (void* const)0xcccccccc;
#endif
#define WINassert(expr) assert(expr)
#else // not WIN32
#define WINassert(expr) ((void)0)
#endif


//Get a dynamic string from input
char* getDynamicWord() {
    size_t len = 4;
    size_t sz = 0;
    char* word = (char*)malloc(len + 1);
    assert(word != NULL && "fail to create word array!");

    // getting characters
    char ch;
    while ((ch = getchar()) != EOF && !isspace(ch)) {
        // increasing the buffer size if needed
        if (sz == len) {
            char* wordBigger = (char*)realloc(word, ((len *= 2) + 1));
            assert(wordBigger != NULL && "fail to create wordBigger array!");
            if (wordBigger == NULL) {
                free(word);
            }
            word = wordBigger;
        }

        // storing the char
        word[sz++] = ch;
    }

    // checking if the last character is EOF or whitespace
    if (ch != EOF)
        ungetc(ch, stdin);

    // storing the terminating character
    word[sz] = 0;

    
    // return the character array
    return word;
}

// Get a list of values from input stream and store them in an dynamic sized array
double* getDynamicArray() {
    size_t capacity = 4;
    size = 0; //global variable instantiation
    double* numbers = (double*)malloc((capacity + 1) * sizeof(double));
    assert(numbers != NULL && "fail to create numbers array!");

    double num;
    while (1) {

        //check the size and capacity and double it if more space is needed
        if (size == capacity) {
            double* biggerNumber = (double*)realloc(numbers, (((capacity *= 2) + 1) * sizeof(*biggerNumber)));
            assert(biggerNumber != NULL && "fail to create biggerNumber array!");
            if (biggerNumber == NULL) {
                free(numbers);
            }
            numbers = biggerNumber;
        }

        //if is a number store the value in the array
        if (scanf("%lf", &num) == 1) {
            numbers[size++] = num;
        }
        else {
            char* word = getDynamicWord();
            if (strcmp(word, "end") == 0)
                break;
            else if (getchar() == EOF)
                break;
        }

    }

    //returning the array
    return numbers;
}