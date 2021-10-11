//This file does not contain the 'main' function.
//This is a helper file


#include "statsHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include<string.h>
#include <inttypes.h>
#include<math.h>

// create functions

//create sorting part
int compare_double(const void* a, const void* b)
{
	double arg1 = *(const double*)a;
	double arg2 = *(const double*)b;

	return (arg1 > arg2) - (arg1 < arg2);
}

//create sorting part
void quicksort(double number[], int first, int last) {
	int i, j, sorting;
	double temp;
	if (first < last) {
		sorting = first;
		i = first;
		j = last;

		//loop
		while (i < j) {
			while (number[i] <= number[sorting] && i < last)
				i++;
			while (number[j] > number[sorting])
				j--;
			if (i < j) {
				//swaping
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}
		}
		//swaping
		temp = number[sorting];
		number[sorting] = number[j];
		number[j] = temp;
		//recursion 
		//call the function again
		quicksort(number, first, j - 1);
		quicksort(number, j + 1, last);
	}
}
//print array to check the sorting
void printArray(double store[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%.3lf ", store[i]);
	printf("\n");
}
//create line
void printLine() {
	int line = 205;
	for (int i = 0; i < 100; i++) {
		printf("%c", line);
	}
	printf("\n");
}

//maxNUmber create
double maxNumber(double arr[], size_t size) {
	double largeNumber = 0;
	for (size_t j = 0; j < size; j++) {
		if (j == 0) {
			largeNumber = arr[0];
		}
		if (largeNumber < arr[j]) {
			largeNumber = arr[j];
		}
	}
	return largeNumber;
}
//minNumber create
double minNumber(double arr[], size_t size) {
	double smallper = 0;
	for (size_t j = 0; j < size; j++) {
		if (j == 0) {
			smallper = arr[0];
		}
		if (smallper > arr[j]) {
			smallper = arr[j];
		}

	}
	return smallper;

}

//histogram coding
void histogramCode(double Percent[]) {
	//ASCII values
	int graph = 254, line = 196, topDivider = 194, downDivider = 193, straightLine = 179, topCorner = 218, bottonCorner = 192;

	//max number
	double Largeper = maxNumber(Percent, 10);
	double Smallper = 0;

	//start
	printf("\n");
	printf("\n");
	printf("Grp       %%  0");
    //modulus to adjust the graph points
	double result = fmod(Largeper, 5.00);
	// the variable to store the rest of the value after subtraction from 5 to adjust the value of graph point
	double logPercentLength;
	for (size_t j = 0; j < 10; j++) {
		if (result == 0) {
			logPercentLength = (Largeper) / 10;
			Smallper += logPercentLength;
			printf("%6.1lf", Smallper);
		}
		else {
			logPercentLength = (Largeper + (5 - result)) / 10;
			Smallper += logPercentLength;
			printf("%6.1lf", Smallper);
		}


	}
	printf("\n");
    //create the line length and design
	printf("%c%c%c%c%c%c%c%c%c%c%c%c %c", line,line, line, line, line, line, line, line, line, line, line, line, topCorner);
	int ch = 65;
	for (size_t j = 0; j < 10; j++) {

		printf("%c%c%c%c%c%c", line, line, line, line, line, topDivider);

	}
	printf("\n");
	
	for (size_t j = 0; j < 10; j++) {

		printf(" %c  %5.1lf%%   %c", ch, Percent[j], straightLine);
		//here Smallper is the hightest point of graph point
		double graphLength = floor((Percent[j] * 60) / Smallper);

		for (int i = 0; i < graphLength; i++) {
			printf("%c", graph);
		}
		ch++;
		printf("\n");
	}
	//line formating
	printf("%c%c%c%c%c%c%c%c%c%c%c%c %c",line, line, line, line, line, line, line, line, line, line, line, line, bottonCorner);

	for (size_t j = 0; j < 10; j++) {
		printf("%c%c%c%c%c%c", line, line, line, line, line, downDivider);

	}
	
}

//create frequency table
void frequency(double numberArray[], double smallNumber, size_t numOfValue, double bucketLength, double percentage[]) {
	double firstInclude = 0, lastExclude = 0, logFirst = 0, logLast = 0;
	int count[10] = { 0 };
	int ch = 65;

	for (size_t j = 0; j < 10; j++) {

		//initializing the frequency renges
		if (j == 0) {
			firstInclude += smallNumber;
		}
		else {
			firstInclude = lastExclude;
		}
		lastExclude = firstInclude + bucketLength;

		if (j == 9) {
			//last one will be included
			//loop for count the number in a specific range
			for (size_t i = 0; i < (size_t)numOfValue; i++) {
				//numberArray[i] <= lastExclude
				if (numberArray[i] >= firstInclude) {
					count[j]++;
					//printf("insert ");

				}

			}
		}
		else {

			//last one will be included
			for (size_t i = 0; i < (size_t)numOfValue; i++) {

				if (numberArray[i] >= firstInclude && numberArray[i] < lastExclude) {
					count[j]++;
				}

			}


		}
		//print the frequency table
		if (j == 9) {
			percentage[j] = (100 * (double)count[j]) / (double)numOfValue;
			printf(" %c [%5.1lf .. %6.1lf ] = %6d:  %7.2lf%%\n", ch, firstInclude, lastExclude, count[j], percentage[j]);
			//ch++;
		}
		else {
			percentage[j] = (100 * (double)count[j]) / (double)numOfValue;
			printf(" %c [%5.1lf .. %6.1lf ) = %6d:  %7.2lf%%\n", ch, firstInclude, lastExclude, count[j], percentage[j]);
			//ch++;
		}
		ch++;

	}
}

