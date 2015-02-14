#ifndef ABC_HELLO_HPP
#define ABC_HELLO_HPP 1.0

/* Hello,
 * 
 * This header includes just enough to make sure that the tool box is working.
 * A call to abc::HelloWorld will print to output to establish that the
 * tool box is getting
 */

//#include "../private/hello-world.h"



namespace abc
{
void HelloWorld (void);
/* The small "hello world" function. It prints hello world to stdout.
 * Prams.: void
 * Effect: Prints a message to the standard output.
 * Return: void
 * Timing: constaint
 * Except: no-throw
 */
}

#endif//ABC_HELLO_HPP
