#include "ff-scanner-base.hpp"

// Implementation of the entire core of the scanner classes.

#include "ff-static-base.hpp"



namespace abc
{
// Constructors and Deconstructor: ===========================================
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
// This got put here early because it deals with the format pointer.
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

// Implementation Functions: =================================================

}
