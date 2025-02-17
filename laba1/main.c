#include "funcs.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Pattern : %s <filename>\n", argv[0]);
        return 1;
    }

    char choice;
    do {
        printf("\nMenu:\n");
        printf("1 - Enter array and write in file\n");
        printf("2 - Print array from file\n");
        printf("3 - Count elements that greater than sum of previous\n");
        printf("4 - Insert element before as close as possible element\n");
        printf("5 - Swap even pairs in file\n");
        printf("0 - Exit\n");
        printf("Choose action: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                inputArrayToFile(argv[1]);
                break;
            case '2':
                printArrayFromFile(argv[1]);
                break;
            case '3':
                countGreaterThanSum(argv[1]);
                break;
            case '4':
                insertElementInFile(argv[1]);
                break;
            case '5':
                swapEvenPairsInFile(argv[1]);
                break;
            case '0':
                printf("Exit ;D \n");
                break;
            default:
                printf("Incorrect input.Try again.\n");
        }
    } while (choice != '0');

    return 0;
}
