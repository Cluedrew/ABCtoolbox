#include "ABCff-format.h"

/* Implementation of the FFFormat class.
 * This is never visible to the end user, but allows overlap of some of the
 * internals of the
 */



namespace abc
{
// Constructors and Deconstructor: *******************************************
FFFormat::FFFormat (std::string & format_) :
  uses(0), format(format_)
{}

FFFormat::~FFFormat ()
{}



// Use tracking: *************************************************************

// Adds to the number of uses of this FFFormat.
void FFFormat::UseThis()
{
  ++uses;
}

// Decreases the number of uses of this and return if it is now unused.
bool FFFormat::StopUse()
{
  --uses;
  return !uses;
}

}
