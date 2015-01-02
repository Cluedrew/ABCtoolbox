#ifndef ABCDEF_TERMINAL_H
#define ABCDEF_TERMINAL_H

/* The Terminal class allows for grid based use of consol, instead of the
 * command line style it usually has.
 */



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
  /*
   * Prams.:
   * Effect:
   * Return:
   */
  
  
  
  RapidInput (bool rapid = true);
  /*
   * Prams.:
   * Effect:
   * Return:
   */
  
  ShowEcho (bool show = true);
  /*
   * Prams.:
   * Effect:
   * Return:
   */
  
  
  
  void Refresh ();
  /* Update the terminal display to show any changes written to it.
   * Prams.: void
   * Effect: Refresh the entire terminal.
   * Return: void
   */
  
  
  
  int GetCh();
  /*
   * Prams.:
   * Effect:
   * Return:
   */
  
  PutCh(char);
  /*
   * Prams.:
   * Effect:
   * Return:
   */
  
  Print(char);
  Print(char const *);
  Print(std::string);
  
  /*
   * Prams.:
   * Effect:
   * Return:
   */
};

}

#endif//ABCDEF_TERMINAL_H
