/*
 * Floating Point Encodings.c
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
	float f = 15213.0f;

    printf ("\nIEEE-754 Single-Precision representation of: %f\n\n", f);
    show_ieee754 (f);

    return 0;
}
