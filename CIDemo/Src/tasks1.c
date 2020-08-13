/**
  * Polyspace example.
  * This file defines the high-level procedures for the tasking examples.
  *       Copyright 2012-2015 The MathWorks, Inc.
  */

#include "include.h"


typedef struct {
    int A;
    int B;
} rec;


/* Internal function         */
/* Needed for MISRA-rule 8.1 */
static void initregulate(void);
static void tregulate(void);
static void Tserver(void);
static void server2(void) ;
static void server1(void);
static void proc1(void);
static void proc2(void);


/* Global variables */
int PowerLevel = 0;

static rec SHR4;
static int SHR5 = 5;
static int SHR = 0;
static int SHR2 = 0;
static int SHR6;


int orderregulate(void)
{
    int tmp, X;
    Increase_PowerLevel();
    SHR4.A = 22;
    tmp = PowerLevel + SHR4.A;

    X = tmp;
    return X;
}


static void initregulate(void)
{
    int tmp = 0;
    while (random_int() < 1000) {
        tmp = orderregulate();
        Begin_CS();
        tmp = SHR + SHR2 + SHR6;
        End_CS();
        tmp = Get_PowerLevel();
        Compute_Injection();
    } /* end loop; */
}


static void tregulate(void)
{
    if (random_int() > 0)
        initregulate();

    while (random_int() > 0) {
        orderregulate();
    }
}


static void Tserver(void)
{
    int I = 1;
    SHR2 = 22;
    orderregulate();
    while (I < 10000) {
        I = I + 1;
        Begin_CS();
        SHR = 22 + SHR6;
        End_CS();
        Exec_One_Cycle(I);
    }
    SHR2 = 0;
}


static void server2(void)
{
    Tserver();
}


static void server1(void)
{
    Tserver();
}


static void proc1(void)
{
    SHR5 = SHR5 + 23;
}


static void proc2(void)
{
    static int SHR3 = 0;

    SHR4.B = 22;
    SHR3 = SHR3 + 1 + SHR4.B + SHR5;
}
