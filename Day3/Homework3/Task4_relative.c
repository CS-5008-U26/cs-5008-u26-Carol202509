/* 
 * Print the ET-function for each integer from 2 to a given number.
 *
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0) { // Base case: if b is 0, return a
        return a;
    }
    return gcd(b, a % b); // Recursive call with b and the remainder of a divided by b
}

// Function to calculate the ET-function for a given number x
int et(int x) {
    int count = 0;
    for (int i = 1; i < x; i++) { // Loop through integers from 1 to x-1
        if (gcd(i, x) == 1) { // If the GCD of i and x is 1, they are coprime
            count += 1;
        }
    }
    return count;
}

int main () {
    char s[100];
    int num; // the number input by the user

    printf("Enter a number: "); // Prompt the user for input
    scanf("%d", &num); // Read the input number

    // Print the ET-function for each integer from 2 to num
    for (int i = 2; i <= num; i++) {
        printf("ET(%d) = %d\n", i, et(i));
    }

    fgets(s,100,stdin);
    return 0;
}