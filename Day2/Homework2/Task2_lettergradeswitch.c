/* Task 2: letter grade program - Homework 2
 * 
 * Print a letter grade based on a numeric score from 1 to 10 (switch version).
 * 
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main (){

    int numberScore;

    printf("Please enter your number score: ");
    scanf("%d", &numberScore);

    switch (numberScore) {
        case 1:
        case 2:
        case 3:
            printf("Your letter grade is: F\n");
            break;
        case 4:
        case 5:
            printf("Your letter grade is: E\n");
            break;
        case 6:
            printf("Your letter grade is: D\n");
            break;
        case 7:
            printf("Your letter grade is: C\n");
        case 8: 
            printf("Your letter grade is: B\n");
            break;
        case 9:
        case 10:
            printf("Your letter grade is: A\n");
            break;
        default:
            printf("Error: The number score must be between 1 and 10.\n");
            break;
    }

    return 0;
}