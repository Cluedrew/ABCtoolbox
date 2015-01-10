#include "ff-static-base.hpp"

namespace abc
{
// Constructors and Deconstructor: ===========================================
FFStaticBase::FFStaticBase (std::string const & format_) :
  uses(1), format(format_)
{}

FFStaticBase::~FFStaticBase ()
{}



// Implementation functions: =================================================

// Turns out there are none, it is all handled by the scanner.

}//abc
