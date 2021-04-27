/*
 * Floating Point Rounding.c
 *
 *  Created on: 27 Apr 2021
 *      Author: Grant
 */

#include <stdio.h>
#include <stdint.h>
#include <limits.h> /* for CHAR_BIT */
#include <math.h>

/** formatted output of ieee-754 representation of float */
void show_ieee754 (float f)
{
    union {
        float f;
        uint32_t u;
    } fu = { f };

    int i = 32;

    while (i--)
        printf ("%d ", (fu.u >> i) & 0x1);
}

int main (void)
{
	float a = 67.0/32.0;
	float b = 35.0/16.0;
	float c = 23.0/8.0;
	float d = 21.0/8.0;

    printf ("\nIEEE-754 Single-Precision representation of a: %f\n\n", a);
    show_ieee754 (a);
    printf("\n");

    printf ("\nIEEE-754 Single-Precision representation of b: %f\n\n", b);
    show_ieee754 (b);
    printf("\n");

    printf ("\nIEEE-754 Single-Precision representation of c: %f\n\n", c);
    show_ieee754 (c);
    printf("\n");

    printf ("\nIEEE-754 Single-Precision representation of d: %f\n\n", d);
    show_ieee754 (d);
    printf("\n");

    float a1 = round(a*4)/4.0;
    float b1 = round(b*4)/4.0;
    float c1 = round(c*4)/4.0;
    float d1 = round(d*4)/4.0;

    printf ("\nIEEE-754 Single-Precision representation of a1: %f\n\n", a1);
    show_ieee754 (a1);
    printf("\n");

    printf ("\nIEEE-754 Single-Precision representation of b1: %f\n\n", b1);
    show_ieee754 (b1);
    printf("\n");

    printf ("\nIEEE-754 Single-Precision representation of c1: %f\n\n", c1);
    show_ieee754 (c1);
    printf("\n");

    printf ("\nIEEE-754 Single-Precision representation of d1: %f\n\n", d1);
    show_ieee754 (d1);
    printf("\n");

    return 0;
}
