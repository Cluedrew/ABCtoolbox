#ifndef ABC_FF_SCANNER_HPP
#define ABC_FF_SCANNER_HPP

// Scan through formatted files to get input.



/* FFScanner is the main class used to scan from files.
 * 
 * For your convenunce most functions that require strings will accept std
 * library string objects or c-strings
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
 * %#: ...
 * 
 * Input Tokens:
 * 
 * %s: string, reads in character until a character matching the one following
 *     the token is found. ? May not be followed directly by another token.
 * 
 * %w: word (equivant to %s% ?)
 * 
 * %l:
 */

// Upgrade: convert the scanner into a template so it can be initated for
// different types of characters (like string and w_string).

#endif//ABC_FF_SCANNER_HPP
