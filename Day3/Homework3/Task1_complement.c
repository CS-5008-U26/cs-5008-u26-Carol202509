/* 
 * Write a program that reads an integer and prints the 10's complement.
 *
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>
/*
 * Function to recursively calculate the 10's complement of an integer
 * by replacing each digit with (9 - digit)
 */
int complement(int x) {
    int rightmostDigit; // the rightmost digit of the integer
    int complementOfRightmostDigit; // the complement of the rightmost digit
    int remainingDigits; // the remaining digits of the integer after removing the rightmost digit

    rightmostDigit = x % 10; // get the rightmost digit of x
    complementOfRightmostDigit = 9 - rightmostDigit; //complement it
    remainingDigits = x / 10; //remove the rightmost digit from x

    // base case: if there are no more digits left, return the complement of the rightmost digit
    if (remainingDigits == 0) {
        return complementOfRightmostDigit;
    }
    // recursive case: calculate the complement of the remaining digits
    // then combine it with the complement of the rightmost digit
    else {
        return complement(remainingDigits) * 10 + complementOfRightmostDigit;
    }
}

int main () {
    char s[100];
    int x; // the integer input by the user
    
    printf("Enter an integer: "); // prompt the user to enter an integer
    scanf("%d", &x); // read the integer

    if (x < 0) { // if the input is negative, print an error message and exit
        printf("Error: Please enter a positive integer.\n");
        return 1;
    }
    
    // call the complement function and print the result
    printf("The complement is %d\n", complement(x));

    fgets(s,100,stdin);
    return 0;
}