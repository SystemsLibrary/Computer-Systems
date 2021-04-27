/*
 * Floating Point Addition.c
 *
 *  Created on: 27 Apr 2021
 *      Author: Grant
 */

#include <stdio.h>
#include <stdint.h>
#include <limits.h> /* for CHAR_BIT */

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
	float f = 15.5f;
	float g = 12.5f;
	float h = f + g;

    printf ("\nIEEE-754 Single-Precision representation of: %f\n\n", f);
    show_ieee754 (f);
    printf("\n");

    printf ("\nIEEE-754 Single-Precision representation of: %f\n\n", g);
    show_ieee754 (g);
    printf("\n");

    printf ("\nIEEE-754 Single-Precision representation of: %f\n\n", h);
    show_ieee754 (h);
    printf("\n");

    return 0;
}
