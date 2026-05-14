/* A First C Program - for Homework 1
 *
 * This code will start you off.  Modify it as instructed in Homework 1.
 * 
 * Put your name here: Carol(Xin Wang)
 * CS-5008 Spring 2025
 */

/* Standard Libraries */
#include <stdio.h>

/**** MAIN PROGRAM ****/

int main() {

    int x, y, sum;
    char s[100];

    printf("Enter a number: \n");
    scanf("%d", &x);
    fgets(s,100,stdin);
    
    printf("Enter another number: \n");
    scanf("%d", &y);
    fgets(s,100,stdin);

    sum = x + y;

    printf("Their sum is %d\n", sum);

    fgets(s,100,stdin);
}