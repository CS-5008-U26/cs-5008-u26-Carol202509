/* 
 * Print the prime factors of a given number using looping and conditional statements.
 *
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main () {
    char s[100];
    int num; // the number input by the user
    int factor; // the current factor
    
    printf("Enter a number: "); // Prompt the user for input
    if (scanf("%d", &num) != 1 || num <= 1) { // Read and validate the input number
        printf("Please enter an integer greater than 1.\n");
        return 1;
    }

    factor = 2; // Start with the smallest prime factor
    printf("The prime factors are ");
    while (num > 1) {
        if (num % factor == 0 ) { // If the current factor is a factor of num
            num = num / factor; // Divide num by the factor to reduce it
            if (num == 1) {
                printf("%d", factor); // Print the last factor without a *
            }
            else {
                printf("%d * ", factor); // Print the factor followed by *
            }
        }
        else {
            factor++; // Move to the next potential factor
        }
    }
    printf("\n");
    fgets(s,100,stdin);
    return 0;
}