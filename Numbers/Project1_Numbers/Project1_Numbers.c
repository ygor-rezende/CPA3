/**
*   Program Name: Project1_Numbers.c
 *  Purpose: Get a number as input in the range of 0 to 4294967295 and return a series of analysis results
 *           about the number read.
 *  Coder: Ygor Lopez de Rezende
 *  Date: Jan 25, 2021
*/

#define _CRT_SECURE_NO_WARNINGS //keep Microsoft quiet about _s
#define LLINT long long int      
#define UINT_MIN 0
#define MAX_SIZE 33 // maximum size of the binary number array

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int index = 0; // global variable to hold the index used on binary conversion function

/*******METHODS AREA*******/
//evaluate if the number is odd or even
bool isEven(size_t num)
{
    return num % 2 == 0;
}//end method

//evaluate if the number is triangular
bool isTriangular(LLINT num)
{
    //the formula is: (sqrt(8x + 1) - 1) / 2. The result has to be an integer
    if ((((size_t)sqrt((8 * num) + 1) - 1) % 2) == 0 && num != 0) // casting here is necessary because sqrt function returns a double
        return true;
    else
        return false;
}//end method

//evaluate if the number is prime or composite
bool isPrime(size_t num)
{
    size_t factor = 2;
    if (num < 2)
    {
        return false;
    }
    else
    {
        while (num > factor)
        {
            if (num % factor == 0)
                return false;
            else
                ++factor;
        }
        return true;
    }
}// end method


// evaluate if the number is square
bool isSquare(size_t num)
{
    if (num == 0)
        return true;
    else
        return fmod(num, sqrt(num)) == 0;
}// end method

//evaluate if the number is power of two
bool isPowerOfTwo(size_t num)
{
    if (num == 0)
        return false;
    else
        return log2(num) == ceil(log2(num));
}// end method

//evaluate if the number is factorial
bool isFactorial(size_t num)
{
    //the only two numbers that are equal to their factorial 
    return num == 1 || num == 2;
}//end method

//evaluate if the number is a Fibonacci number
bool isFibonacci(size_t num)
{
    size_t a = 1;
    size_t f = 0;
    size_t b = 0;
    for (size_t i = 1; i <= num + 1; ++i)
    {
        b = a + f;
        f = a;
        a = b;
        if (num == f)
            return true;
    }
    return false;
}//end method

//evaluate if the number is perfect, deficient or abundant
int isPerfect_Deficient_Abundant(size_t num)
{
    /**
    * Returns:
        -1 if the number is deficient
         0 if the number is perfect
         1 if the  number is abundant
    */
    if (isPrime(num) || num == 1) {
        return -1;
    }
    else
    {
        size_t sum = 1;
        for (size_t i = 2; i < num; ++i)
        {
            if (num % i == 0)
                sum += i;
        }
        if (sum < num)
            return -1;
        else if (sum == num)
            return 0;
        else
            return 1;
    }
}// end method


// convert the number to binary
int* convertBinary(size_t num)
{
    // declaring the array as static in order to return the correct values stored
    int* binary = calloc(MAX_SIZE, sizeof(int));
    if (binary == NULL)
        return NULL;
    binary[MAX_SIZE - 1] = 0;
    for (index = MAX_SIZE - 1; num > 0; --index)
    {
        binary[index] = num % 2;
        num = num / 2;
    }
    return binary;

}//end method

// evaluate the Even parit bit
int getEvenParitBit(int num[])
{
    int sum = 0;
    for (int i = index; i < MAX_SIZE; ++i)     // the stop condition is using the global variable index to sum only the values assigned into the array
    {
        sum += num[i];
    }
    return sum % 2;
}//end method

// count the number's number of digits 
int countDigits(size_t num)
{
    if (num == 0)
        return 1;
    int count = 0;
    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}//end method

// evaluate if the number is a palindrome
bool isPalindromic(size_t num, size_t end)
{
   if (end <= 1)
        return true;
   char* sNum = (char*)malloc(end + 1);
   if (sNum == NULL)
         return NULL;

    sprintf(sNum, "%zu", num);
    size_t beg = 0;
    while (beg < --end)
    {
        if (sNum[beg] != sNum[end])
                return false;
        beg++;
    }
    free(sNum);
    return true;
}// end method

// print the number with thousand separators. Ex: 1,000
void printSeparators(size_t num, int nDigits)
{
    printf("\nThe number with thousand separators is ");
    if (nDigits < 4)
    {
        printf("%zu", num);
    }
    else
    {
        char* sNum = (char*)malloc(nDigits + 1);
        if (sNum == NULL)
            perror("Error");
        else
            sprintf(sNum, "%zu", num);
        char* reverseNum = (char*)malloc(nDigits + (nDigits / 3));
        int count = 0;
        for (int i = nDigits - 1; i >= 0; i--)
        {
            if (reverseNum && sNum) {
                reverseNum[count] = sNum[i];
                if ((nDigits - i) % 3 == 0 && i > 0)
                    reverseNum[++count] = ',';
                count++;
            }
           
        }
        for (int i = count - 1; i >= 0; i--)
        {
                printf("%c", reverseNum[i]);
            }
        free(sNum);
        free(reverseNum);
    }
    

}//end method

/***********MAIN PROGRAM************/
int main()
{
    LLINT inNumber = 0;  // input variable declaration        
    bool isValid = true;

    // 1) Program title
    printf("Project 1: Numbers, Ygor Lopez de Rezende, Jan 2021\n\n");

    // 2) getting a valid input
    do
    {
        printf("Enter a number in the range [%+u..%+u]: ", UINT_MIN, UINT32_MAX);

        // checking if the input is a number
        while (1)
        {
            if (scanf("%lld", &inNumber) != 1)
            {
                printf("ERROR! Not a number!\nPlease enter an integer in the range [%+u..%+u]: ", UINT_MIN, UINT32_MAX);
                int ch;
                while ((ch = getchar()) != EOF && ch != '\n'); //cleaning the buffer
            }
            else
            {
                break;
            }

        }//end while
        // checking if the input is in the range
        if (inNumber < UINT_MIN || inNumber > UINT32_MAX)
        {
            printf("ERROR! ");
            isValid = false;
            int ch;
            while ((ch = getchar()) != EOF && ch != '\n'); //cleaning the buffer
        }
        else
        {
            isValid = true;
        }
    } while (!isValid);
    size_t number = inNumber;

    // 3) check if the number is odd or even through the method isEven()
    if (isEven(number))
        printf("\nThe number is even.");
    else
        printf("\nThe number is odd.");

    // 4) check if the number is triangular through the method isTriangular()
    if (isTriangular(number))
        printf("\nThe number is triangular.");
    else
        printf("\nThe number is not triangular.");

    // 5) check if the number is prime or composite through the method isPrime()
    if (isPrime(number))
        printf("\nThe number is prime.");
    else
        printf("\nThe number is composite.");

    // 6) check if the number is square through the method isSquare()
    if (isSquare(number))
        printf("\nThe number is square.");
    else
        printf("\nThe number is not square.");

    // 7) check if the number is a power of 2 through the method isPowerOfTwo()
    if (isPowerOfTwo(number))
        printf("\nThe number is a power of 2.");
    else
        printf("\nThe number is not a power of 2.");

    // 8) check if the number is factorial through the method isFactorial()
    if (isFactorial(number))
        printf("\nThe number is a factorial.");
    else
        printf("\nThe number is not a factorial.");

    // 9) check if the number is fibonacci through the method isFibonacci()
    if (isFibonacci(number))
        printf("\nThe number is a fibonacci number.");
    else
        printf("\nThe number is not a fibonacci number.");

    // 10) check if the number is perfect, deficient or abundant
    if (isPerfect_Deficient_Abundant(number) == -1)
        printf("\nThe number is deficient.");
    else if (isPerfect_Deficient_Abundant(number) == 0)
        printf("\nThe number is perfect.");
    else
        printf("\nThe number is abundant.");

    // 11) Getting and printing the even parit bit
    // First converting the number to binary using a pointer to receive the returnig array values form the method
    int* numBin = convertBinary(number);
    printf("\nEven parit bit: %d", getEvenParitBit(numBin));

    // 12) check the number of digits
    size_t numDigits = countDigits(number);
    printf("\nThe number has %d digit(s).", numDigits);

    // 13) check if the number is palindromic
    if (isPalindromic(number, numDigits))
        printf("\nThe number is palindromic.");
    else
        printf("\nThe number is not palindromic.");

    // 14) print the number in binary
    printf("\nThe number in binary: ");
    if (number == 0) {
        printf("%d", number);
    }
    else {
        for (int i = index; i < MAX_SIZE - 1 || i == index; ++i)
        {
            printf("%d", numBin[i + 1]);
        }
    }

    // 15) Printing the number entered with thousands separators (,)
    printSeparators(number, numDigits);

    free(numBin);
    return 0;
}// end main
