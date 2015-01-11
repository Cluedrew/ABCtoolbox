#ifndef ABCDEF_TERMINAL_HPP
#define ABCDEF_TERMINAL_HPP

/* The Terminal class allows for grid based use of consol, instead of the
 * command line style it usually has.
 */

#include <string>



namespace abc
{
class Terminal
{
private:
  static Terminal * instance;
  
protected:
  Terminal ();
  
public:
  virtual ~Terminal ();
  
  static Terminal * CreateTerminal ();
  /* If a terminal does not already exist, create a new one.
   * Prams.:
   * Effect:
   * Return: Pointer to new Terminal if one was created, otherwise null.
   */
  
  static Terminal * GetInstance ();
  /* Return any existing instance of a Terminal.
   * Prams.: void
   * Effect: void
   * Return: A Terminal pointer to the exist terminal.
   */
  
  
  /* All option functions default to the starting value. 
   */
  
  void RapidInput (bool rapid = true);
  /* Use input immediately or wait for a newline command line style.
   * Prams.: 
   * Effect:
   * Return: void
   */
  
  void StdControlChars (bool use = true);
  /* Choose to use the standard control character behavours or to override them.
   * Prams.:
   * Effect:
   * Return: void
   */
  
  void ShowEcho (bool show = true);
  /* Control wheither to show the echo of the users input or hide it.
   * Prams.:
   * Effect:
   * Return: void
   */
  
  //void UseKeypad (bool use = true);
  /* [Is that the most approprate name?]
   * Prams.:
   * Effect:
   * Return: void
   */
  
  
  
  void Refresh (void);
  /* Update the terminal display to show any changes written to it.
   * Prams.: void
   * Effect: Refresh the entire terminal.
   * Return: void
   */
  
  loc Cursur ();
  void Cursur (int & x, int & y);
  /* Get information on the cursur's location.
   * Prams.:
   * Effect:
   * Return:
   */
  
  bool MoveC (int const & x, int const & y);
  bool MoveC (loc const & l);
  /* Move the cursur to a set x,y coordinates on the terminal.
   * Prams.:
   * Effect:
   * Return:
   */
  
  
  
  int GetCh(void);
  /* Read in the next character and return it.
   * Prams.:
   * Effect:
   * Return:
   */
  
  void PutCh(int);
  /* Print out a character with the given id.
   * Prams.:
   * Effect:
   * Return:
   */
  
  
  
  void Print(char);
  void Print(char const *);
  void Print(std::string);
  /* Print out a value in a human readable form.
   * Prams.:
   * Effect:
   * Return:
   */
  
  char ReadChar ();
  std::string ReadString ();
  /* Read in a type from a human readable form.
   * Prams.:
   * Effect:
   * Return:
   */
  
  /*
   * Prams.:
   * Effect:
   * Return:
   */
};

}

#endif//ABCDEF_TERMINAL_HPP
