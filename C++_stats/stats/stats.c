//This file contains the 'main' function.

/* ! file  :   stats.c
  *	author :Agnita Paul
  *	date   :2021-06-25

  *	note   MSVC:   /std:c17
  *	note   GNUC:   -std=c17
*/ 



#define _CRT_SECURE_NO_WARNINGS
#include "statsHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include<string.h>
#include <inttypes.h>
#include<math.h>



/*!	This program receives command line arguments.
*
*	argc:	the number of commandline argument
*	argv:	an array of pointers to contain strings of the commandline arguments
*/



int main(int argc, char* argv[]) {

	//stdin for keybord input

	FILE* stream = stdin;

	// check for arguments...
	if (argc > 2) {
		printf("Error: too many command-line arguments (%d)\n", argc);
		printf("Usage: stats [filename]\n");
		return EXIT_FAILURE;
	}

	//for file read
	if (argc == 2) {
		stream = fopen(argv[1], "r");
		if (stream == NULL) {
			printf("error <%s> ", argv[1]);
			perror(" ");
			return EXIT_FAILURE;
		}
	}
	
	//for keyboard input's instruction: 
	if (argc == 1) {
		printf("Enter a list of whitespace-separated real numbers terminated by EOF or 'end'.\n");
	}
	
	//declare variables
	char* endingPoint;
	double number;
	long numOfValue = 0;
	size_t j = 0;
	double totalNumber = 0;
	double smallNumber = 0, largeNumber = 0;
	size_t capacity = 1;
	size_t size = 0;

	//Memory allocate
	double* numberArray = (double*)malloc((capacity + 1) * sizeof(double));
	if (numberArray == NULL) {
		return NULL;
	}
	char tempString[20] = { 0 };

	//read the file or keybaord 
	while (fscanf(stream, "%s", tempString) != EOF) {

		//ending point
		if (!strcmp(tempString, "end")) {
			break;
		}

		//Memory reallocate
		if (size == capacity) {	// expand if full
			capacity += 1;
			double* reallocate = (double*)realloc(numberArray, (capacity + 1) * sizeof(double));	// if moves, it copies, then frees

			if (reallocate == NULL) {
				free(numberArray);
				return NULL;

			}
			//store value in numberArray
			numberArray = reallocate;

		}

		//convertion string to double
		number = strtod(tempString, &endingPoint);
		//number of values of dynamic array
		numOfValue++;
		//store the value in the array
		numberArray[size++] = number;

		//total number of values addition of array
		totalNumber += number;

	}
	
	//line 
	printLine();

	//max and min number
	smallNumber = minNumber(numberArray, numOfValue);
	largeNumber = maxNumber(numberArray, numOfValue);
	//numberArray[size] = '\0';

	//to fulfill the project .. this is the output of num of value, max,min range,mean, median, variance, std
	printf("# elements %30li\n", numOfValue);
	printf("minimum    %30.3lf\n", smallNumber);
	printf("maximum    %30.3lf\n", largeNumber);
	//range
	double range = largeNumber - smallNumber;
	printf("range      %30.3lf\n", range);
	//printf("size: %zu\n", size);
	double mean = totalNumber / size;
	printf("mean       %30.3lf\n", mean);
	
	//closing the file or stream
	fclose(stream);

	//quicksort(numberArray, 0, numOfValue - 1);
	qsort(numberArray, numOfValue, sizeof(double), compare_double);

	//printf("\nSorted array is \n");
	//printArray(numberArray, numOfValue);

	//median
	int medianIndex;
	double median = 0;
	if (numOfValue % 2 != 0) {
		medianIndex = (numOfValue - 1) / 2;
		median = numberArray[medianIndex];
		printf("median     %30.3lf\n", median);
	}
	else {
		int medianIndex1 = numOfValue / 2;
		int medianIndex2 = (numOfValue - 1) / 2;
		double median1 = numberArray[medianIndex1];
		double median2 = numberArray[medianIndex2];
		median = (median1 + median2) / 2;
		printf("median     %30.3lf\n", median);

	}
	//standard deviation  
	//variance
	double standardDeviation = 0, variance = 0;
	double totalSubtract = 0;
	for (size_t i = 0; i < (size_t)numOfValue; i++) {
		totalSubtract += (numberArray[i] - mean) * (numberArray[i] - mean);
		//printf("store again : %zu - %d\n", i, store[i]);
	}
	variance = totalSubtract / numOfValue;
	printf("variance   %30.3lf\n", variance);
	standardDeviation = sqrt(variance);
	printf("std. dev.  %30.3lf\n", standardDeviation);
	//line
	printLine();
	printf("Frequency Table \n\n");

	//to make frequency table, it is the length between the each frequency group
	double bucketLength = (double)(range) / 10;
	double logBucketLength = (log(range)) / 10.0;
	
	//take array to store percentage value
	double percentage[10] = { 0 }, logPercent[10] = { 0 };

	//to printf the alphabet
	int ch = 65;

	//call frequency table
	frequency(numberArray, smallNumber, numOfValue, bucketLength, percentage);

	//histogram
	printf("\n");
	printLine();
	printf("Histogram ");
	histogramCode(percentage);

	//Log frequency table
	printf("\n");
	printLine();
	printf("Log Frequency Table ");
	printf("\n");
	printf("\n");

	//create a dynamic array to store the log values
	double* logNumberArray = (double*)malloc(numOfValue * sizeof(double));
	if (logNumberArray == NULL) {
		return NULL;
	}
	for (int i = 0; i < numOfValue; i++) {
		logNumberArray[i] = log(numberArray[i]);
	}
	//call frequency table function
	double smallLog = minNumber(logNumberArray, numOfValue);
	frequency(logNumberArray, smallLog, numOfValue, logBucketLength, logPercent);

	free(logNumberArray);
	

	//log histogram
	printf("\n");
	printLine();
	printf("Log Histogram ");
	histogramCode(logPercent);
	
}