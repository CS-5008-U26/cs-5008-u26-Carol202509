/* 
 * Print the prime factors of a given number using a recursive function.
 *
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

void primeFactors(int num, int factor) {
    // base case: if num is reduced to 1, return
    if (num == 1) {
        return;
    }
    
    if (num % factor == 0) { // If the current factor is a factor of num
        printf("%d", factor); // Print the current factor
        if (num / factor != 1) { // If there are more factors to print, print a *
            printf(" * ");
        }
        primeFactors(num / factor, factor); // recursive call with reduced num
    }
    else {
        primeFactors(num, factor + 1); // recursive call with the next potential factor
    }
}

int main () {
    char s[100];
    int num; // the number input by the user
    
    printf("Enter a number: "); // Prompt the user for input
    scanf("%d", &num); // Read the input number

    if (num <= 1) { // Validate the input number
        printf("Error:Please enter an integer greater than 1.\n");
        return 1;
    }

    printf("The prime factors are: ");
    primeFactors(num, 2);
    printf("\n");
    
    fgets(s,100,stdin);
    return 0;
}