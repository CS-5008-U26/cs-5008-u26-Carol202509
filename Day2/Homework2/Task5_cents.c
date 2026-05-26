/* Task 5: cents program - Homework 2
 * 
 * Print the number of quarters, dimes, nickels and pennies needed in a given number of cents.
 * 
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main () {
    int cents;
    int quarters;
    int dimes;
    int nickels;
    int pennies;

    /* ask user to input a number of cents between 1 and 100 */
    printf("Enter a number of cents between 1 and 100: ");
    scanf("%d", &cents);
    
    /* check if the number of cents is between 1 and 100 */
    if (cents < 1 || cents > 100) {
        printf("Error: The number of cents must be between 1 and 100.\n");
        return 1;
    }

    quarters = cents / 25; // calculate the number of quarters
    cents %= 25;  // what is left after calculating quarters

    dimes = cents / 10;  // calculate the number of dimes
    cents %= 10;  // what is left after calculating dimes

    nickels = cents / 5;  // calculate the number of nickels
    cents %= 5;  // what is left after calculating nickels

    pennies = cents;  // the remaining cents

    printf("That requires ");

    if (quarters > 0) {
        printf("%d %s", quarters, quarters == 1 ? "quarter" : "quarters");
    }
    if (dimes > 0) {
        printf("%s%d %s", quarters > 0 ? ", " : "", dimes, dimes == 1 ? "dime" : "dimes");
    }
    if (nickels > 0) {
        printf("%s%d %s", quarters > 0 || dimes > 0 ? ", " : "", nickels, nickels == 1 ? "nickel" : "nickels");
    }
    if (pennies > 0) {
        printf("%s%d %s", quarters > 0 || dimes > 0 || nickels > 0 ? ", and " : "", pennies, pennies == 1 ? "penny" : "pennies");
    }
    printf(".\n");

    return 0;
}