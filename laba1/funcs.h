//
// Created by Maksim on 16.02.2025.
//


#define FUNCS_H



#include <stdlib.h>
#include <stdio.h>


void inputArrayToFile(char *filename);
void printArrayFromFile(char *filename);
int countGreaterThanSum(char* filename);
void insertElementInFile(char *filename, int newValue);
void swapEvenPairsInFile( char *filename);
void countGreaterThanSumFinal(char *filename);
int getNewValue();
void task2(char* filename);
void swapNumbersInFile(FILE *file, long pos1, int num1, long pos2, int num2);



