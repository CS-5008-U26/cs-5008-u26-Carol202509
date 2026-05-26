/* Task 4: radius program - Homework 2
 * 
 * Print the area of a circle given its radius.
 * 
 * Carol(Xin Wang)
 * CS-5008 Summer 2026
 */

#include <stdio.h>
#include <math.h>

int main () {
    int radius;
    double pi;
    int area;

    pi = acos(-1);

    printf("Enter an integer radius: ");
    scanf("%d", &radius);

    /* check if the radius is positive */
    if (radius < 0) {
        printf("Error: The radius must be a positive integer.\n");
        return 1;
    }

    area = (int)(pi * radius * radius);

    printf("For a circle of radius %.1f the area is %d\n", (double)radius, area);

    return 0;
}