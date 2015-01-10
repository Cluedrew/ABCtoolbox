#include "ff-scanner.hpp"

// Implementation of the entire core of the scanner classes.

#include "ff-static-base.hpp"



namespace abc
{
// Constructors and Deconstructor: ===========================================
FFScanner::FFScanner (std::string const & format) :
  format(new FFStaticBase(format))
{}

FFScanner::FFScanner (FFScanner const & other) :
  format(other.format)
{
  // Mark that the format is being used.
  ++other.format->uses;
}

FFScanner::~FFScanner ()
{
  // Mark that the format is no longer being used.
  if (0 == --format->uses)
    delete format;
}



// Operator Overload =========================================================
// This got put here early because it deals with the format pointer.
FFScanner & FFScanner::operator= (FFScanner const & other)
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
// Access: ===================================================================

// File Operations: ==========================================================

// Spacer Extractors: ========================================================

// Reading Extractors: =======================================================

// Error Handling: ===========================================================

}//abc
