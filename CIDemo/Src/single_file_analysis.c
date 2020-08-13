/**
  * Polyspace example.
  *       Copyright 2012-2015 The MathWorks, Inc.
  */

#include "single_file_analysis.h"
#include "single_file_private.h"
#include "include.h"

/*
   global variables declaration
   input variables for the module/function/file
*/
static u16 v0;
static s16 v1;
static s16 v2;
static u8 v3;
static s16 v4;
static s16 v5;

/* output variables for the module/function/file */
static s32 output_v6;
static s32 output_v7;
static s8 output_v1;

static s16 saved_values[127];


/* function definitions */

all_values(s32)
all_values(s16)
all_values(u16)

/* Internal function         */
/* Needed for MISRA-rule 8.1 */
static s32 new_speed(s32 in, s8 ex_speed, u8 c_speed);
static char reset_temperature(u8 in_v3);
static void functional_ranges(void);
static s32 unused_fonction(void);


static void functional_ranges(void)
{
    /*  sets all global variables to their functional range */
    v0 = all_values_u16(0 * BIN_v0,  90 * BIN_v0);

    v1 = all_values_s16(0 * BIN_v1,   90 * BIN_v1);
    v2 = all_values_s16(-810 * BIN_v2,  150 * BIN_v2);
    v3 = (u8)all_values_s32(0 * BIN_v3,   54 * BIN_v3);
    v4 = all_values_s16(-45 * BIN_v4,  126 * BIN_v4);

    v5 = all_values_s16(-90 * BIN_v5,  900 * BIN_v5);
}


static s32 new_speed(s32 in, s8 ex_speed, u8 c_speed)
{
    return (in / 9 + ((s32)ex_speed + (s32)c_speed) / 2);
}


static char reset_temperature(u8 in_v3)
{
    int array[255-(54 * BIN_v3)];

    return array[in_v3-255] = 0;
}


s8 generic_validation(s8 extrapolated_speed, u8 computed_speed)
{
    /**************************************************************
     * Input parameters                                           *
     *           NAME                      POSSIBLE VALUES        *
     *      s8 extrapolated_speed              [ -128 ; 127 ]     *
     *      u8 computed_speed                  [    0 ; 255 ]     *
     **************************************************************
     * Output values                                              *
     *           NAME                      POSSIBLE VALUES        *
     *      s8 ret               NA_VALUE (-128), or [ -46; 126 ] *
     **************************************************************/
    s32 s32_ret;
    s16 v0_c;
    s8 s8_ret;

    /*  sets all global variables to their functional range */
    functional_ranges();

    v0_c = (s16) gVALUE(v0);
    if (v0_c == 90) {
        return (s8) NA_VALUE;
        /* grey explanation
         * when initialized, v0 is truncated to [ 0 ; 26624]
         * instead of [ 0 ; 92160 ] (92160 = 90 * BIN_v0)
         *
         * Note:
         *        90 * BIN_v0 = 90 * 1024 = 92160
         *        and  92160 MOD [ 0 ; 65535] = 26624
         */
    }

    if (v1 >= 60 * BIN_v1) {
        output_v6 = gVALUE(v2) * gVALUE(v4) / gVALUE(v1);
    } else {
        output_v6 = gVALUE(v3) * gVALUE(v1) - gVALUE(v5);
    }
    output_v7 = new_speed(output_v6, extrapolated_speed, computed_speed);
    s32_ret = new_speed(output_v7, extrapolated_speed, computed_speed) / 2;


    s8_ret = (s8) NA_VALUE;
    /* the return value spec indicates that it should be between [ -50 ; 126 ] */
    if ((s32_ret < -50) || (s32_ret >  126)) {
        /* if dead code, we can remove this test
         *   - gain in execution speed
         *   - gain for the other developers who don't need to test the return
         *     value against NA_VALUE (-128)
         */
        SEND_MESSAGE(s32_ret, "%d out of functional bounds reached");
    } else {
        s8_ret = (s8) s32_ret;
        output_v1 = s8_ret + 15;
    }

    if (output_v7 >= 0) {
        saved_values[output_v7] = s8_ret;
        return s8_ret;
    }
    return reset_temperature(v3);
}


static s32 unused_fonction(void)
{
    return saved_values[output_v1] + (s32) generic_validation((output_v6 / 10000) , (output_v7 / 16000));
}
