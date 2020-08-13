/**
  * Polyspace example.
  *       Copyright 2012-2015 The MathWorks, Inc.
  */

#include <math.h>
#include "include.h"

/* polyspace:begin<MISRA-C3:D4.6:High:Fix>  Add a types.h file, create typedefs and replace inbuilt types  */
/* polyspace:begin<MISRA-C:5.7:Not a defect:No Action planned> The reused names in this function actual seem to be appropriate uses of scoping */


/* Internal function         */
/* Needed for MISRA-rule 8.1 */
static int get_oil_pressure(void);
static void Close_To_Zero(void);
static int Non_Infinite_Loop(void);
static void Pointer_Arithmetic(void);
static void Recursion(int* depth);
static void Recursion_caller(void);
static void Square_Root_conv(double alpha, float* beta_pt);
static void Square_Root(void);
static void Unreachable_Code(void);
/* polyspace<MISRA-C3:8.7:Low:Investigate> should have internal linkage! */
extern int get_bus_status(void);


static int get_oil_pressure(void)
{
    volatile int vol_i;
    int i;
    i = vol_i;
    assert(i > 0);
    return i;
}


/* Here we demonstrate PolySpace Verifier's ability to
   distinguish between values which are very close to
   zero, and zero itself.
*/
static void Close_To_Zero(void)
{
    float xmin = random_float();
    float xmax = random_float();
    float y;

    if ((xmax - xmin) < 1.0E-37f) {
        y = 1.0f;
    } else {
        /* division by zero is impossible here */
        y = (xmax + xmin) / (xmax - xmin);
    }
}


/* Here we demonstrate the ability to abstract out a very large number
   of iterations.  Please note that this is done in linear time, since
   PolySpace Verifier models the dynamic behavior, without execution.

   The loop must iterate 2**31 times before y>big allows it to break out.

   Correct operation is demonstrated because:
   1) x = x + 2 is shown to never generate an overflow
   2) the loop is not infinite
*/
static int Non_Infinite_Loop(void)
{
    const int big = 1073741821 ;  /* 2**30-3 */
    int x = 0, y = 0;

    while (1)

    {
        if (y > big) { break;}
        x = x + 2;
        y = x / 2;
    }

    y = x / 100;
    return y;
}


/* Here we demonstrate PolySpace Verifier's ability to track a
   pointer across numerous pointer arithmetic operations,
   including invalid addresses and back to valid addresses.
*/
static void Pointer_Arithmetic(void)
{
    int array[100];
    int i, *p = array;

    for (i = 0; i < 100; i++) {
        *p = 0;
        p++;
    }

    if (get_bus_status() > 0) {
        if (get_oil_pressure() > 0) {
            *p = 5; /* Out of bounds */
        } else {
            i++;
        }
    }

    i = get_bus_status();

    /* polyspace<MISRA-C3:18.4:Not a defect:No action planned>Purpose is to show PolySpace can find pointer errors - pointers are often deemed necessary and code verification is the mitigation */
    if (i >= 0)  {*(p - i) = 10;}

    if ((0 < i) && (i <= 100)) {
        /* polyspace<MISRA-C3:18.4:Not a defect:No action planned> Purpose is to show PolySpace can find pointer errors - pointers are often deemed necessary and code verification is the mitigation */
        p = p - i;
        *p = 5;     /* Safe pointer access */
    }
}


/* Here we demonstrate PolySpace Verifier's ability to trace
   dynamic arithmetic properties across a recursion loop.

   The main function Recursion() takes a parameter, increments it,
   then divides by it.  This sequence of actions loops through
   an indirect recursive call to Recursion_recurse().

   If the initial value passed to Recursion() is negative, then
   the recursive loop will at some point attempt a division
   by zero.
*/
static void Recursion(int* depth)
/* if depth<0, recursion will lead to division by zero */
{
    float advance;

    *depth = *depth + 1;
    advance = 1.0f / (float)(*depth); /* potential division by zero */


    if (*depth < 50) {
        /* polyspace<MISRA-C3:17.2:Not a defect:No action planned> Purpose is to show that PolySpace can spot problems with recursive code*/
        Recursion(depth);
    }
}


static void Recursion_caller(void)
{
    int x = random_int();


    if ((x > -4) && (x < -1)) {
        Recursion(&x);     // always encounters a division by zero
    }


    x = 10;
    if (random_int() > 0) {
        Recursion(&x);     /* never encounters a division by zero */
    }
}


/*
   Here we demonstrate PolySpace Verifier's ability to trace numeric
   constraints across many different arithmetic operations.
   The table provided below the example shows the domain of
   values for the expressions in the example.
*/

static void Square_Root_conv(double alpha, float* beta_pt)
/* Perform arithmetic conversion of alpha to beta */
{
    *beta_pt = (float)((1.5 + cos(alpha)) / 5.0);
}


static void Square_Root(void)
{
    double alpha = random_float();
    float beta;
    /* polyspace<MISRA-C3:5.3:Not a defect:No Action planned> Gamma is the appropriate name */
    float gamma;

    Square_Root_conv(alpha, &beta);

    gamma = (float)sqrt(beta - 0.75);   /* always sqrt(negative number) */
}


static void Unreachable_Code(void)
/* Here we demonstrate PolySpace Verifier's ability to
    identify unreachable sections of code due to the
    value constraints placed on the variables.
*/
{
    int x = random_int();
    int y = random_int();

    if (x > y) {
        x = x - y;
        if (x < 0) {
            x = x + 1;
        }
    }

    x = y;
}


void RTE(void)
/* Group together calls generating interesting RTE checks */
{
    int tmp;
    Close_To_Zero();

    if (random_int() > 0) {
        tmp = Non_Infinite_Loop();
    }

    Pointer_Arithmetic();

    Recursion_caller();

    if (random_int() > 0) {
        Square_Root();
    }

    Unreachable_Code();

}

/* polyspace:end<MISRA-C:5.7:Not a defect:No Action planned> The reused names in this function actual seem to be appropriate uses of scoping */

/* polyspace:end<MISRA-C3:D4.6:High:Fix>  Add a types.h file, create typedefs and replace inbuilt types  */
