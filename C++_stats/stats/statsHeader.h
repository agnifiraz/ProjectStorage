//header

#define _CRT_DEBUG_MAP_ALLOC
#include<crtdbg.h>
#include<stdlib.h>

//all functions
int compare_double(const void* a, const void* b);
void quicksort(double number[], int first, int last);
void printArray(double store[], int size);
void printLine();
double maxNumber(double arr[], size_t size);
double minNumber(double arr[], size_t size);
void histogramCode(double logPercent[]);
void frequency(double numberArray[], double smallNumber, size_t numOfValue, double bucketLength, double percentage[]);




