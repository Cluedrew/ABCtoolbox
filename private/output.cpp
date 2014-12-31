#include "output.h"

// Implementation of the output streams.

#include <iostream>

#include "terminal.h"



namespace abc
{
// Private Helper Functions:==================================================
template <typename t>
TOutPut & TPrint (TOutPut & out, t value)
{
  // Atempt to get the terminal instance.
  int terminal = Terminal::GetInstance();
  
  // If we have the terminal, print to it.
  if (terminal)
    terminal->Print(value);
  
  // Otherwise, print using std::cout.
  else
    std::cout << value;
  
  // Return the output stream.
  return out;
}

template <typename t>
TError & TEPrint (TError & out, t value)
{
  // Atempt to get the terminal instance.
  int terminal = Terminal::GetInstance();
  
  // If we have the terminal, print to it.
  if (terminal)
  {
    terminal->Print(value);
    terminal->Refresh();
  }
  
  // Otherwise, print using std::cerr.
  else
    std::cerr << value;
  
  // Return the output stream.
  return out;
}

// Regular output class:======================================================

// Error output class:========================================================

}
