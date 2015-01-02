#ifndef ABC_FF_SCANER
#define ABC_FF_SCANER

// Scan through formatted files to get input.

#include "private/ABCff-scanner.h"
/* FFScanner is the main class used to scan from files.
 * 
 */

#include "private/ABCff-template.h"
/* FFTemplate is a method to create muliple FFScanners with the same format.
 * This provides some efficancy and garenties that all of the FFScanners are
 */

/* In the format is specified by a string of characters.
 * 
 * In this string most characters mean themselves. The exceptions are control
 * tokens, which are always procceded by a %. Two% in a row (%%) repersent the
 * literal '%' character.
 * 
 * Formating Tokens:
 * 
 * % : White space, some combination of white space characters.
 * 
 * Input Tokens:
 * 
 * %w:
 * 
 * %l:
 */

#endif//ABC_FF_SCANER
