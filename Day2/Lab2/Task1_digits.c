/* Takes in a number from the user and sums up the digits, then prints it.
*/

#include <stdio.h>

int main () {
    int number;
    int sum = 0;
    int remainder;

    printf("Please enter an integer: \n"); // Get the number from the user
    scanf("%d", &number);

    remainder = number;

    while (remainder > 0) {
        sum += (remainder % 10); // Add the last digit to the sum
        remainder /= 10; // Remove the last digit
        }

    printf("The sum of the digits is %d\n", sum);

}