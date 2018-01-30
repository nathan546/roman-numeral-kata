/*******************************************************************
* 
*
* DESCRIPTION :      Header enumeration, strings, and functions for main.c parsing states
*                    See main.c for more information
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

#include "roman_numeral_calculator.h"
#include "check_roman_numeral_calculator.h"
#include "roman_numeral_operations_list.h"

static char * mainMenu = "\r\nMain Menu - Roman Numeral Calculator Kata Exercise\r\n" \
                         "\t1) Run Addition Test Story\r\n" \
                         "\t2) Run Subtraction Test Story\r\n" \
                         "\t3) Run Complete Induction Test Story\r\n" \
                         "\t4) Manually Enter Roman Numeral Expression\r\n" \
                         "\t5) Quit\r\n" \
                         "\t6) Open Source Software List\r\n";

static char * manualMainMenu = "\r\nManual Menu - Manual Operations\r\n" \
                               "\t1) Run Roman Numeral Addition Calculation\r\n" \
                               "\t2) Run Roman Numeral Subtraction Calculation\r\n" \
                               "\t3) Run Decimal to Roman Numeral Converter\r\n" \
                               "\t4) Run Roman Numeral to Decimal Converter \r\n" \
                               "\t5) Return to main menu\r\n";


static char * completeInductionDescript = \
      "\r\n\tIn theory -- Proof By Complete Induction (Brute Force) \r\n\r\n" \
      "\t    With the exception of number system's overflows (>3999), underflows (<=0), and invalid user inputs,\r\n" \
      "\t    we can prove our roman numeral calculator works in all cases by proving that it can convert from:\r\n" \
      "\t       - Any decimal value (1-3999) to the correct roman numeral value (I to MMMCMXCIX)\r\n" \
      "\t       - Any roman numeral value (I to MMMCMXCIX) to the correct decimal value (1-3999) \r\n" \
      "\t    If these two cases can be proven, then we can convert any roman numeral inputs to their decimal equivalents,\r\n" \
      "\t    perform basic decimal addition/subtraction on them, and then convert the result back to a roman numeral equivalent\r\n\r\n" \
      "\t    The file, complete_induction.equations contains 3999 lines (of the form 1=I, 2=II, etc) that provide an input for this proof\r\n\r\n";  


static char * additionStoryDescript = \
      "\r\n\tAddition Story -- \r\n\r\n" \
      "\t    This story reads in the story_addition.equations file and compares each line\r\n" \
      "\t    for a valid addition operation.  Input lines from the file are of the form I+I=II,\r\n" \
      "\t    so the source will add I+I internally and ensure the result is II using libcheck\r\n";

static char * subtractionStoryDescript = \
      "\r\n\tSubtraction Story -- \r\n\r\n" \
      "\t    This story reads in the story_subtraction.equations file and compares each line\r\n" \
      "\t    for a valid subtraction operation.  Input lines from the file are of the form II-I=I,\r\n" \
      "\t    so the source will subtract II-I internally and ensure the result is I using libcheck\r\n";     

static char * fossList = \
      "\r\n\tThis is a free open source software notice letting the user know that the program uses: \r\n" \
      "\t    Libcheck (LGPLV2) from https://github.com/libcheck/check\r\n" \
      "\t    Libsubunit (Apache & BSD) from https://github.com/testing-cabal/subunit\r\n";

//Parsing states for main command line
enum {ADDITION_STORY='1', SUBTRACTION_STORY='2', COMPLETE_INDUCTION='3', MANUAL_ENTRY='4', QUIT='5', FOSS_LIST='6'};

//Parsing states for MANUAL_ENTRY sub command line
enum {MANUAL_ADDITION='1', MANUAL_SUBTRACTION='2', MANUAL_DEC_TO_RN='3', MANUAL_RN_TO_DEC='4', MANUAL_QUIT='5'};

//Private functions
static void doRomanNumeralToDecimal();
static void doDecimalToRomanNumeral();
static void doManualOperation(ROMAN_NUMERAL_OPERATION * romanNumeralOperation);
static bool getValue(char * input, bool (*functionPointer)(char*));
static void flushInput();
static bool isNumericChar(char * input);
static char getAlphanumericChar();
static void manualEntry();

#endif
