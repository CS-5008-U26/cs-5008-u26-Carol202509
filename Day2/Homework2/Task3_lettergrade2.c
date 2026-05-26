/* Task 3: letter grade program - Homework 2
 * 
 * Print a letter grade based on a numeric score from 0 to 100.
 * 
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main (){

    int numberScore;
    
    printf("Enter your number score: ");
    scanf("%d", &numberScore);

    /* check if the number score is between 0 and 100 */
    if (numberScore < 0 || numberScore > 100) {
        printf("Error: The number score must be between 0 and 100.\n");
        return 1;
    }
    
    /* determine the letter grade based on the number score */
    char letterGrade;

    if (numberScore <= 60) {
        letterGrade = 'F';
    }
    else if (numberScore <= 70) {
        letterGrade = 'D';
    }
    else if (numberScore <= 80) {
        letterGrade = 'C';
    }
    else if (numberScore <= 90) {
        letterGrade = 'B';
    }
    else {
        letterGrade = 'A';
    }
    
    /* determine the last digit of the number score to determine if it is a plus, minus, or regular grade */
    int lastDigit = numberScore % 10;

    if (letterGrade == 'F') {
        printf("Your grade is: F\n");
    }
    else {
        switch ( lastDigit ) {
            case 1:
            case 2:
            case 3:
                printf("Your grade is: %c-\n", letterGrade);
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                printf("Your grade is: %c\n", letterGrade);
                break;
            case 8:
            case 9:
            case 0:
                printf("Your grade is: %c+\n", letterGrade);
                break;
            default:
                printf("Your grade is: %c\n", letterGrade);
                break;
        }
    }

    return 0;
}