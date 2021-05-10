/*
 * Optimisation.c
 *
 *  Created on: 10 May 2021
 *      Author: Grant
 */

#include <time.h>
#include <stdio.h>
#include <string.h>

void set_row_original(double *a, double *b, long i, long n)
{
    long j;
    for (j = 0; j < n; j++)
    {
        a[n*i + j] = b[j];
    }
}

void set_row_optimised(double *a, double *b, long i, long n)
{
    long j;
    long ni = n*i;
    double* rowp = a + ni;
    for (j = 0; j < n; j++)
    {
        *rowp++ = b[j];
    }
}

void set_row_2d_original(double *a, double *b, long n)
{
    long i;
    long j;
    for (i = 0; i < n; i++)
    {
        long ni = n*i;
        for (j = 0; j < n; j++)
        {
            a[ni + j] = b[j];
        }
    }
}

void set_row_2d_optimised(double *a, double *b, long n)
{
    long i;
    long j;
    long ni = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            a[ni + j] = b[j];
        }
        ni += n;
    }
}

void direction_original(double *val, long n)
{
    long i;
    long j;
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            long up = val[(i - 1)*n + j];
            long down = val[(i + 1)*n + j];
            long left = val[i*n + j - 1];
            long right = val[i*n + j + 1];
            long sum = up + down + left + right;
        }
    }
}

void direction_optimised(double *val, long n)
{
    long i;
    long j;
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            long inj = i*n + j;
            long up = val[inj - n];
            long down = val[inj + n];
            long left = val[inj - 1];
            long right = val[inj + 1];
            long sum = up + down + left + right;
        }
    }
}

void lower_case_original(char *s)
{
    unsigned int i;
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] -= ('A' - 'a');
        }
    }
}

void lower_case_optimised(char *s)
{
    unsigned int i;
    unsigned int len = strlen(s);
    for (i = 0; i < len; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] -= ('A' - 'a');
        }
    }
}

void sum_reverse_original(double *a, double *b, long n)
{
    long i, j;
    for (i = 0; i < n; i++)
    {
        b[i] = 0;
        for (j = 0; j < n; j++)
        {
            b[i] += a[i*n + j];
        }
    }
}

void sum_reverse_optimised(double *a, double *b, long n)
{
    long i, j;
    for (i = 0; i < n; i++)
    {
        double val = 0;
        long in = i*n;
        for (j = 0; j < n; j++)
        {
            val += a[in + j];
        }
        b[i] = val;
    }
}

struct vec
{
    int len;
    int data[1000];
};

int get_vec_element(struct vec v, unsigned int idx, int *val, int vec_length)
{
    if (idx >= vec_length)
    {
        return 0;
    }

    *val = v.data[idx];
    return 1;
}

void combine_original(struct vec v, int* dest, int vec_length)
{
    long i;

    *dest = 100;
    for (i = 0; i < vec_length; i++)
    {
        int val;
        get_vec_element(v, i, &val, vec_length);
        *dest = *dest * val;
    }
}

void combine_optimise(struct vec v, int* dest, int vec_length)
{
    long i;

    int t = 100;
    for (i = 0; i < vec_length; i++)
    {
        t = t * v.data[i];
    }
    *dest = t;
}

void combine_optimise_unrolling(struct vec v, int* dest, int vec_length)
{
    long i;

    int t = 100;

    for (i = 0; i < vec_length; i += 2)
    {
        t = t * (v.data[i] * v.data[i+1]);
    }

    for (; i < vec_length; i++)
    {
        t = t * v.data[i];
    }
    *dest = t;
}

void combine_optimise_unrolling_accumulators(struct vec v, int* dest, int vec_length)
{
    long i;

    int x0 = 100;
    int x1 = 100;

    for (i = 0; i < vec_length; i += 2)
    {
        x0 = x0 * v.data[i];
        x1 = x1 * v.data[i+1];
    }

    for (; i < vec_length; i++)
    {
        x0 = x0 * v.data[i];
    }
    *dest = x0 * x1;
}

int main()
{
    double a1[10000];
    double b1[10000];

    double a2[10000];
    double b2[100];

    double a3[10000];

    char a4[1000000];
    for (int i = 0; i < 1000000; i++)
    {
        a4[i] = 'A';
    }
    a4[1000000 - 1] = '\0';

    double a5[10000];
    double b5[100];



    struct vec a6;
    a6.len = 100;
    for (int j = 0; j < 1000; j++)
    {
        a6.data[j] = 1;
    }
    int b6[0];
    b6[0] = 100;

    clock_t start = clock();

    for (int y = 0; y < 100; y++)
    {
    	//set_row_original(a1, b1, 0, 10000); //0.004
    	//set_row_optimised(a1, b1, 0, 10000);  //0.003

    	//set_row_2d_original(a2, b2, 100);     //0.003
    	//set_row_2d_optimised(a2, b2, 100);    //0.003

    	//direction_original(a3, 100);            //0.008
    	//direction_optimised(a3, 100);             //0.006

    	//sum_reverse_original(a5, b5, 100);       //0.005
    	//sum_reverse_optimised(a5, b5, 100);        //0.003

    	//combine_original(a6, b6, 1000);            //0.008
    	//combine_optimise(a6, b6, 1000);            //0.001
    	//combine_optimise_unrolling(a6, b6, 1000);  //0.001
    	//combine_optimise_unrolling_accumulators(a6, b6, 1000);  //0.001
    }

    //lower_case_original(a4);   //undefined
    //lower_case_optimised(a4);    //0.274

    clock_t stop = clock();
    //double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f", elapsed);

    return 0;
}
