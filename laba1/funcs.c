//
// Created by Maksim on 16.02.2025.
//


#include "funcs.h"

void inputArrayToFile(char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int n;
    printf("Enter number of elements: ");
    scanf_s("%d", &n);

    int temp;
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf_s("%d", &temp);
        fwrite(&temp, sizeof(temp), 1, file);
    }


    fclose(file);
}




void printArrayFromFile(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int num;
    printf("Elements of array: ");
    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d ", num);
    }
    printf("\n");
    fclose(file);

}

int countGreaterThanSum(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    int count = 0, sum = 0, num;

    while (fread(&num, sizeof(int), 1, file)) {
        if (num > sum) {
            count++;
        }
        sum += num;
    }

    fclose(file);
    return count;
}


void countGreaterThanSumFinal(char *filename) {
    int count = countGreaterThanSum(filename);
    printf("Number of elements greater than the sum of previous: %d\n", count);
}

int getInsertPosition(FILE* file, int newValue) {

    int num, closestIndex = -1, closestDiff = INT_MAX, pos = 0;
    int insertPos = 0;

    while (fread(&num, sizeof(int), 1, file)) {
        int diff = abs(num - newValue);
        if (diff < closestDiff) {
            closestDiff = diff;
            closestIndex = pos;
            insertPos = ftell(file) - sizeof(int);
        }
        pos++;
    }


    return insertPos;
}


void task2(char* filename) {

    int newValue;
    printf("Enter number to insert: ");
    scanf_s("%d", &newValue);

    insertElementInFile(filename, newValue);



}

void insertElementInFile(char *filename, int newValue) {
    FILE *file = fopen(filename, "rb+");
    if (!file) {
        perror("Error opening file");
        return;
    }



    int insertPos = getInsertPosition(file, newValue);

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    int temp;

    for (int i = fileSize - sizeof(int); i >= insertPos; i -= sizeof(int)) {
        fseek(file, i, SEEK_SET);
        fread(&temp, sizeof(int), 1, file);
        fseek(file, i + sizeof(int), SEEK_SET);
        fwrite(&temp, sizeof(int), 1, file);
    }


    fseek(file, insertPos, SEEK_SET);
    fwrite(&newValue, sizeof(int), 1, file);


    fclose(file);
}



void swapNumbersInFile(FILE *file, long pos1, int num1, long pos2, int num2) {
    fseek(file, pos1, SEEK_SET);
    fwrite(&num2, sizeof(int), 1, file);
    fseek(file, pos2, SEEK_SET);
    fwrite(&num1, sizeof(int), 1, file);
}


void processEvenNumbers(FILE *file) {
    int firstEven = -1, secondEven = -1;
    long firstPos = -1, secondPos = -1;
    int num;
    long pos = 0;

    while (fread(&num, sizeof(int), 1, file)) {
        if (num % 2 == 0) {
            if (firstEven == -1) {
                firstEven = num;
                firstPos = pos;
            } else {
                secondEven = num;
                secondPos = pos;
                swapNumbersInFile(file, firstPos, firstEven, secondPos, secondEven);
                firstEven = -1;
                secondEven = -1;
                fseek(file, 0, SEEK_CUR);
            }
        }
        pos = ftell(file);
    }
}

void swapEvenPairsInFile(char *filename) {
    FILE *file = fopen(filename, "r+b");
    if (!file) {
        perror("Error opening file");
        return;
    }
    processEvenNumbers(file);
    fclose(file);
}
