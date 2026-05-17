/* The Third C Program - for Homework 1
 * 
 * Name: Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>

int main() {

    char name[100];
    float principle, interest_rate, interest;
    char s[100];

    printf("Enter your name: \n");
    scanf("%s", name);
    fgets(s,100,stdin);

    printf("Enter your principal amount: \n");
    scanf("%f", &principle);
    fgets(s,100,stdin);

    printf("Enter the interest rate: \n");
    scanf("%f", &interest_rate);
    fgets(s,100,stdin);

    interest = principle * interest_rate;

    printf("Hello, %s! The interest is %f.\n", name, interest);

    fgets(s,100,stdin);
}