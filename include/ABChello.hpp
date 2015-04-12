#ifndef ABC_HELLO_HPP
#define ABC_HELLO_HPP 1.0

/* Hello,
 * 
 * This header includes just enough to make sure that the tool box is working.
 * A call to abc::HelloWorld will print to output to establish that the
 * tool box is getting
 */

#include "../code/hello.world.hpp"
#include "../ABCdefine.hpp"
#include ABCDEF_STR(ABCDEF_PATH(hello-world.hpp))



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
