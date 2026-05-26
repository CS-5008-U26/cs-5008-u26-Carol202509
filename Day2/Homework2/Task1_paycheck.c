/* Task 1: paycheck program - Homework 2
 * 
 * Print a paycheck that are calculated by hours and rate.
 * 
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main () {
    double hourlyRate;
    double numberOfHours;
    double paycheck;

    /* use an infinite while loop to check inputs, the program exits when input is less than or equal to 0 */
    while (1) {
        printf("Enter an hourly rate: ");
        scanf("%lf", &hourlyRate);
        if (hourlyRate <= 0) {
            break;
        }

        printf("Enter the number of hours worked: ");
        scanf("%lf", &numberOfHours);
        if (numberOfHours <= 0) {
            break;
        }

        /* check if number of hours is less than or equal to 40 */
        if (numberOfHours <= 40) {
            paycheck = hourlyRate * numberOfHours;
        }
        /* check if number of hours is greater than 40 */
        else {
            paycheck = hourlyRate * 40 + (numberOfHours - 40) * hourlyRate * 1.5;
        }

        printf("You should be paid %.2lf\n\n", paycheck);
    }

    return 0;
}