/**
  * Polyspace example.
  *       Copyright 2012-2013 The MathWorks, Inc.
  */

#ifndef SINGLE_FILE_ANALYSIS
#define SINGLE_FILE_ANALYSIS

#define NA_VALUE (-128)

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;

/* public interface */
s8 generic_validation(s8 extrapolated_speed, u8 computed_speed);

#endif
