/* Task 6: roman program - Homework 2
 * 
 * Convert a number between 1 and 4000 to its Roman numeral representation.
 * 
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main () {
    int number;
    
    /* ask user to input a number between 1 and 4000 */
    printf("Enter a number between 1 and 4000: ");
    scanf("%d", &number);

    if (number < 1 || number > 4000) {
        printf("Error: The number must be between 1 and 4000.\n");
        return 1;
    }

    printf("The Roman Numeral: ");
    
    // thousands
    while (number >= 1000){
        printf("M");
        number -= 1000; 
    }

    // hundreds
    if (number >= 900) {
        printf("CM");
        number -= 900;
    }
    if (number >= 500) {
        printf("D");
        number -= 500;
    }
    if (number >= 400) {
        printf("CD");
        number -= 400;
    }
    while (number >= 100) {
        printf("C");
        number -= 100;
    }

    // tens
    if (number >= 90) {
        printf("XC");
        number -= 90;
    }
    if (number >= 50) {
        printf("L");
        number -= 50;
    }
    if (number >= 40) {
        printf("XL");
        number -= 40;
    }
    while (number >= 10) {
        printf("X");
        number -= 10;
    }

    // units
    if (number >= 9) {
        printf("IX");
        number -= 9;
    }
    if (number >= 5) {
        printf("V");
        number -= 5;
    }
    if (number >= 4) {
        printf("IV");
        number -= 4;
    }
    while (number >= 1) {
        printf("I");
        number -= 1;
    }

    printf("\n");
    return 0;
}