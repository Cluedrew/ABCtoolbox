#include "ff-scanner-base.hpp"

// Implementation of the entire core of the scanner classes.



namespace abc
{
/* The static base class holds within it all the infromation that is shared
 * between instances of a scanner that have the same format.
 */
class FFStaticBase
{
  // The class is completely private, only allowing FFScannerBase to use it.
  friend class FFScannerBase;
  
  int uses;
  std::string format;
  
  FFStaticBase (std::string const & format_) :
    uses(1), format(format_)
  {}
  
  ~FFStaticBase () {}
};



// FFScannerBase =============================================================

// Constructors and Deconstructor: ===========================================
FFScannerBase::FFScannerBase () :
  format(nullptr)
{}

FFScannerBase::FFScannerBase (std::string const & format) :
  format(new FFStaticBase(format))
{}

FFScannerBase::FFScannerBase (FFScannerBase const & other) :
  format(other.format)
{
  // Mark that the format is being used.
  ++other.format->uses;
}

FFScannerBase::~FFScannerBase ()
{
  // Mark that the format is no longer being used.
  if (0 == --format->uses)
    delete format;
}



// operator overload =========================================================
FFScannerBase const & FFScannerBase::operator= (FFScannerBase const & other)
{
  if (this == &other)
    return other;
  
  // Remove the old format:
  if (0 == --format->uses)
    delete format;
  // Use the new format:
  format = other.format;
  ++format->uses;
  
  return *this;
}

}
