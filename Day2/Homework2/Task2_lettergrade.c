/* Task 2: letter grade program - Homework 2
 * 
 * Print a letter grade based on a numeric score from 1 to 10.
 * 
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main (){

    int numberScore;
    
    printf("Please enter your number score: ");
    scanf("%d", &numberScore);

    if (numberScore ==9 || numberScore == 10) {
        printf("Your letter grade is: A\n");
    }
    else if (numberScore == 8) {
        printf("Your letter grade is: B\n");
    }
    else if (numberScore == 7) {
        printf("Your letter grade is: C\n");
    }
    else if (numberScore == 6) {
        printf("Your letter grade is: D\n");
    }
    else if (numberScore == 4 || numberScore == 5) {
        printf("Your letter grade is: E\n");
    }
    else if (numberScore >= 1 && numberScore <= 3) {
        printf("Your letter grade is: F\n");
    }
    else {
        printf("Error: The number score must be between 1 and 10.\n");
    }

    return 0;
}