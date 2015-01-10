#include "terminal.h"

/* Implementation of the terminal class using ncurses.
 * 
 * It should be noted that the terminal is a singleton class, repersenting
 * the on-screen terminal. The control of the instance pointer has changed
 * a little to (try to) allow sub-classes to exist. However only one
 * instance of this or any sub-class may exist at a time.
 * Also, inherited classes should have their own CreateX functions so that
 * they can be created in a proper singleton way (GetInstance is for all
 * possible classes).
 * 
 * This only has basic features*, although the singleton nature of this
 * class is heavily enforced ncurses still has global access, so inherited
 * classes are free to add extra features on that way.
 * * Simple things that ncurses provides, so this is just a wrapper.
 */

#include <ncurses.h>



namespace abc
{
// Define static member variables:============================================
Terminal::instance = nullptr;



// Constructors and Deconstructor:============================================
Terminal::Terminal ()
{
  // Check that creating the terminal is valid, is so set instance.
  if (instance)
    throw "find an exception for terminal creation.";
  else
    // Will this work on inherited classes?
    instance = this;
  
  // Start ncurses.
  initscr();
  // Do not wait for \n characters.
  cbreak();
  // Activate the keypad. keypad(stdscr, TRUE);
}

Terminal::~Terminal ()
{
  // Remove the instance pointer to the class.
  instance = nullptr;
  
  // Close ncurses.
  endwin();
}



// Singleton Functions:=======================================================
Terminal * Terminal::CreateTerminal ()
{
  // Create a new terminal if one does not already exist.
  return (instance) ? nullptr : new Terminal();
}

Terminal * Terminal::GetInstance ()
{
  return instance;
}



// Implementation Functions:==================================================

// Option Functions:==========================================================

// Control wheither to show the echo of the users input or hide it.
void Terminal::RapidInput (bool rapid)
{
  if (rapid)
    cbreak();
  else
    nocbreak();
}

// Choose to use the standard control character behavours or to override them.
void Terminal::StdControlChars (bool use)
{
  if (use)
    noraw();
  else
    raw();
}

// Control wheither the screen echos the users input. Starts showing echo.
void Terminal::ShowEcho (bool show)
{
  if (show)
    echo();
  else
    noecho();
}

/*/
void Terminal::UseKeypad (bool use)
{
  if (use)
    keypad(stdscr, TRUE);
  else
    keypad(stdscr, FALSE);
}*/



// Control Functions:=========================================================

// Update the terminal display to show any changes written to it.
void Terminal::Refresh ()
{
  refresh();
  // refresh might return an int, see what that means.
}

// Get the cursur's location in the terminal.
loc Terminal::Cursur ()
{
  int x, y;
  getyx(y,x);
  loc fin = {x,y};
  return fin;
}
void Terminal::Cursur (int & x, int & y)
{
  getyx(y,x);
}

// Move the cursur to a set x,y coordinates on the terminal.
bool Terminal::MoveC (int const & x, int const & y)
{
  move(y, x);
  return true;
  // ERR == -1 as error code?
}
bool Terminal::MoveC (loc const & l)
{
  move(l.y, l.x);
  return true;
  // ERR == -1 as error code?
}

// Output Functions:==========================================================

// Input Functions:===========================================================

}//abc
