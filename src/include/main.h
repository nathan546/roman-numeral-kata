/*******************************************************************
* 
*
* DESCRIPTION :      Header enumeration for main.c parsing states
*
* NOTES :            None
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 27, 2018     Nathan Barrett Morrison      Original Code
*
*/

#ifndef MAIN_H

#define MAIN_H

//Parsing states for main command line
enum {ADDITION_STORY='1', SUBTRACTION_STORY='2', COMPLETE_INDUCTION='3', MANUAL_ENTRY='4', QUIT='5'};

//Parsing states for MANUAL_ENTRY sub command line
//enum {MANUAL_ADDITION, MANUAL_SUBTRACTION, MANUAL_DEC_TO_RN, MANUAL_RN_TO_DEC };

#endif
