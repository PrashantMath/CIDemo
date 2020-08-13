/**
  * Polyspace example.
  *       Copyright 2012-2015 The MathWorks, Inc.
  */

#ifndef INCLUDE_H
#define INCLUDE_H
/* polyspace:begin<MISRA-C3:D4.6:High:Fix>  Add a types.h file, create typedefs and replace inbuilt types  */
#define true 1
#define false 0

#define checksum 1
#define new_move 0
#define previous_move 1

#define MAX_SIZE 10

#ifdef DEFINE_TYPES
typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;
typedef double         d64;
typedef float          f32;
#endif


/* automatically stubbed functions */
/* polyspace:begin<MISRA-C3:8.7:Not a defect:No action planned> Code is not yet complete and linkage is yet to be decided */
void SEND_MESSAGE(s32 status, const s8 *message);
s32 read_bus_status(void);
static s32 error_on_bus(void);
extern s32 read_on_bus(void);

/* internal functions */
void initialise_current_data(void);
void compute_new_coordonates(void);
void sort_calibration(void);
s32  polynomia(s32 input);

s32  random_int(void);
f32  random_float(void);
/* polyspace:end<MISRA-C3:8.7:Not a defect:No action planned> Code is not yet complete and linkage is yet to be decided */
extern void partial_init(s32 *new_alt);
/* polyspace<MISRA-C3:8.7:Low:Improve> May only be used here - make a library or make it static */
extern void RTE(void);
/* polyspace<MISRA-C3:8.2:High:Fix> add a named parameter */
extern void Exec_One_Cycle (s32 X);
extern s32  orderregulate (void);
extern void Begin_CS (void);
extern void End_CS (void);
extern void Increase_PowerLevel (void);
extern s32  Get_PowerLevel (void);
extern void Compute_Injection (void);

extern s32 tab[MAX_SIZE];
extern s32 PowerLevel;

extern s32 first_payload;
extern s32 second_payload;
extern s32 *arr;
/* polyspace:end<MISRA-C3:D4.6:High:Fix>  Add a types.h file, create typedefs and replace inbuilt types  */

#endif
