/*!	file		Stats.c
    author		Ygor Lopez de Rezende
    date		2021-03-01

    Receives a data set(series of real numbers) as input and output the statistic results of the data set.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "array_check.h"


// structure to be used in Modes and outliers evaluation
struct stats {
    size_t frequency;
    double value;
    size_t count;
};

// Swap two elements in the heap memory
void swap(double* ele1, double* ele2) {
    double aux = *ele1;
    *ele1 = *ele2;
    *ele2 = aux;
}

//heapify is a complementary method to sort arrays using Heap Sort Method
void heapify(double arr[], int parent, size_t heapSize) {
    int largest;
    while (1) {
        size_t leftNode = parent * 2;
        if (leftNode > heapSize)
            break;
        if (arr[leftNode - 1] > arr[parent - 1])
            largest = leftNode;
        else
            largest = parent;
        size_t rightNode = leftNode + 1;
        if (rightNode <= heapSize && arr[rightNode - 1] > arr[largest - 1])
            largest = rightNode;
        if (largest != parent) {
            swap(&arr[largest - 1], &arr[parent - 1]);
            parent = largest;
        }
        else {
            break;
        }
    }
}

//sort the array numbers using Heap Sort algorithm
void heapSort(double num[]) {
    for (int i = size / 2; i > 0; --i) {
        heapify(num, i, size);
    }
    for (int i = size - 1; i > 0; --i) {
        swap(&num[0], &num[i]);
        heapify(num, 1, i);
    }
}

//calculates the median value
double getMedian(double const numbers[]) {
    if (size % 2 == 0)
        return (numbers[size / 2] + numbers[size / 2 - 1]) / 2;
    else
        return numbers[size / 2];
}

//calculates the mean
double getMean(double const numbers[]) {
    double sum = 0;
    for (size_t i = 0; i < size; ++i)
        sum += numbers[i];
    return sum / size;
}

//calculates the variance
double getVariance(double const numbers[], double const mean) {
    double sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += pow((numbers[i] - mean), 2);
    }
    return sum / size;
}

//check if there is modes
bool checkModes(double const numbers[]) {
    if (numbers[0] == numbers[size - 1])
        return false;
    double aux = numbers[0];
    for (size_t i = 1; i < size; ++i) {
        if (aux == numbers[i])
            return true;
        aux = numbers[i];
    }
    return false;
}

//print the number of modes, frequency and modes values
struct stats* printGetModes(double const numbers[]) {
    struct stats* mode;
    //creates a struct pointer to store mode values if more than 1
    mode = (struct stats*)malloc(size * sizeof(struct stats));
    if (mode == NULL)
        return NULL;
    size_t freq = 1;
    mode->frequency = 0;
    mode->count = 0;
    double element = numbers[0];
    size_t modeIndex = 0;
    for (size_t i = 1; i < size; ++i) {
        if (numbers[i] == element) {
            freq++;
            if ((mode + modeIndex)->value != numbers[i] && freq >= mode->frequency) {
                mode->count++;
                modeIndex = mode->count - 1;
                (mode + modeIndex)->value = numbers[i];
                mode->frequency = freq;
            }
            else if ((mode + modeIndex)->value == numbers[i] && freq > mode->frequency) {
                mode->count = 1;
                modeIndex = mode->count - 1;
                (mode + modeIndex)->value = numbers[i];
                mode->frequency = freq;
            }
        }
        else {
            if (freq > mode->frequency && mode->frequency > 0) {
                mode->frequency = freq;
            }
         freq = 1;
        }
        element = numbers[i];
    }//end for
    printf("# modes %33d\n", mode->count);
    printf("mode frequency %26d\n", mode->frequency);
    printf("modes %35.3lf\n", mode->value);
    if(mode->count > 1)
        for (size_t i = 1; i < mode->count; ++i)
            printf("%41.3lf\n", (mode + i)->value);
    return mode;
}

//calculates mean absolute deviation
double getMeanDeviation(double const numbers[], double const mean) {
    double* absDevArr = (double*)malloc((size + 1) * sizeof(*numbers));
    if (absDevArr == NULL) {
        free(absDevArr);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < size; ++i) {
        *(absDevArr + i) = fabs(numbers[i] - mean);
    }
    heapSort(absDevArr);
    double meanVal = getMean(absDevArr);
    free(absDevArr);
    return meanVal;
}

//calculates median absolute deviation
double getMedianDeviation(double const numbers[], double const median) {
    double* absDevArr = (double*)malloc((size + 1) * sizeof(*numbers));
    if (absDevArr == NULL) {
        free(absDevArr);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < size; ++i) {
        *(absDevArr + i) = fabs(numbers[i] - median);
    }
    heapSort(absDevArr);
    double mean = getMean(absDevArr);
    free(absDevArr);
    return mean;
}

//calculates Xmean
double getXMean() {
    size_t sumX = 0;
    for (size_t i = 0; i < size; ++i) {
        sumX += i;
    }
    return (double)sumX / size;
}

//calculates the regression slope
double getSlope(double const numbers[], double const yMean, double const xMean) {
    double sumX2 = 0;
    double sumXY = 0;
    for (size_t i = 0; i < size; ++i) {
        sumX2 += (double)i * i;
        sumXY += i * numbers[i];        
    }
    double ssxx = sumX2 - (size * xMean * xMean);
    double ssxy = sumXY - (size * xMean * yMean);
    return ssxy / ssxx;
}

//get the regression intercept point
double getIntercept(double const yMean, double const xMean, double const slope) {
    return yMean - (slope * xMean);
}

//print the 2x  and 3x outliers
void printOutliers(double const num[], double const yMean, double const stdDev) {
    struct stats* outlier2x;
    struct stats* outlier3x;
    outlier3x = (struct stats*)malloc(size * sizeof(struct stats));
    if (outlier3x == NULL)
        return NULL;
    outlier2x = (struct stats*)malloc(size * sizeof(struct stats));
    if (outlier2x == NULL)
        return NULL;
    outlier2x->count = 0;
    outlier3x->count = 0;
    size_t outIndex2 = 0;
    size_t outIndex3 = 0;
    double prevValue = num[0];
    for (size_t i = 0; i < size; ++i) {
        if (fabs(num[i] - yMean) > (3 * stdDev) && (prevValue != num[i] || i == 0)) {
            (outlier3x + outIndex3)->value = num[i];
            outlier3x->count++;
            outIndex3++;
        }
        else if (fabs(num[i] - yMean) > (2 * stdDev) && (prevValue != num[i] || i == 0)) {
            (outlier2x + outIndex2)->value = num[i];
            outlier2x->count++;
            outIndex2++;
        }
        prevValue = num[i];
    }
    printf("-----------------------------------------\n");
    printf("Outliers (2x)");
    if (outlier2x->count == 0)
        printf("%28s\n", "no outliers");
    else {
        printf("%24s = %d\n", "# outliers", outlier2x->count);
        for (size_t i = 0; i < outlier2x->count; ++i)
            printf("%41.3lf\n", (outlier2x + i)->value);
    }
    printf("Outliers (3x)");
    if (outlier3x->count == 0)
        printf("%28s\n", "no outliers");
    else {
        printf("%24s = %d\n", "# outliers", outlier3x->count);
        for (size_t i = 0; i < outlier3x->count; ++i)
            printf("%41.3lf\n", (outlier3x + i)->value);
    }
    free(outlier2x);
    free(outlier3x);
}

//calculates and return the mode deviation
double getModeDeviation(double modeVal, double mean) {
    return fabs(modeVal - mean);
}


// Main program
int main()
{

#if defined(_DEBUG) && defined(_WIN32)
    int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);		
    dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;					// check block integrity on every memory call
    dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;					// don't remove blocks on delete (just tag them)
    dbgFlags |= _CRTDBG_LEAK_CHECK_DF;						// check for leaks at process termination
    _CrtSetDbgFlag(dbgFlags);
#endif

    //1) Prompt user to enter a list of numbers
    printf("Enter a list of whitespace-separated real numbers terminated by EOF or 'end'.\n");
    double* numList = getDynamicArray();
    if (numList == NULL) {
        printf("Invalid input!\n");
        return EXIT_FAILURE;
    }
    //2) number of elements
    printf("\n-----------------------------------------\n");
    printf("# elements %30zu\n", size);    
    
    // get a copy of the original array first to use it later
    double* numCopy = (double*)malloc((size+1) * sizeof(*numCopy));
    if (numCopy) {
        for(size_t i = 0; i < size; ++i)
            *(numCopy + i) = *(numList + i);
    }
    

    //3) sorting the array   
    heapSort(numList);
    
    //4) printing the minimum value
    printf("minimum %33.3lf\n", numList[0]);

    //5) printing the maximum value
    printf("maximum %33.3lf\n", numList[size-1]);

    //6) calculate median
    double median = getMedian(numList);
    printf("median %34.3lf\n", median);

    //7) calculate arithmetic mean
    double yMean = getMean(numList);
    printf("mean %36.3lf\n", yMean);

    //8) calculate the variance
    double variance = getVariance(numList, yMean);
    printf("variance %32.3lf\n", variance);

    //9) calculate the standard deviation
    double stdDev = sqrt(variance);
    printf("std. dev. %31.3lf\n", stdDev);

    printf("-----------------------------------------\n");

    //10) calculate modes, modes quantity, and frequency
    struct stats* modes = (struct stats*)malloc(size * sizeof(struct stats));
    if (modes == NULL)
        return EXIT_FAILURE;
    if (checkModes(numList)) {
        modes = printGetModes(numList);
    }
    else {
        printf("# modes %33s\n", "no mode");
    }

    //11)Calculate mean and median absolute deviations
    printf("-----------------------------------------\n");
    printf("mean absolute deviations:\n");
    printf("...about the mean %23.3lf\n", getMeanDeviation(numList, yMean));
    printf("...about the median %21.3lf\n", getMedianDeviation(numList, median));
    if(modes->count == 1)
        printf("...about the mode %23.3lf\n", getModeDeviation(modes->value, yMean));

    //12) Calculate the regression slope and intercept.
    printf("-----------------------------------------\n");
    //calculate x mean
    double xMean = getXMean();

    // using the original array (before sorting)
    double slope = getSlope(numCopy, yMean, xMean);
    printf("regression slope %24.3lf\n", slope);
    printf("regression intercept %20.3lf\n", getIntercept(yMean, xMean, slope));

    //13) Check for outliers 2x and 3x and print
    printOutliers(numList, yMean, stdDev);

    // free the memory...
    free(numCopy);
    free(numList);
    free(modes);
 
    return EXIT_SUCCESS;
}
