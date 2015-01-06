#ifndef ABCDEF_TERMINAL_HPP
#define ABCDEF_TERMINAL_HPP

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
  /* Return any existing instance of a Terminal.
   * Prams.: void
   * Effect: void
   * Return: A Terminal pointer to the exist terminal.
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
  
  
  
  void Refresh (void);
  /* Update the terminal display to show any changes written to it.
   * Prams.: void
   * Effect: Refresh the entire terminal.
   * Return: void
   */
  
  
  
  int GetCh(void);
  /*
   * Prams.:
   * Effect:
   * Return:
   */
  
  void PutCh(int);
  /*
   * Prams.:
   * Effect:
   * Return:
   */
  
  void Print(char);
  void Print(char const *);
  void Print(std::string);
  /*
   * Prams.:
   * Effect:
   * Return:
   */
  
  char         ReadChar ();
  char const * ReadCharStr ();
  std::string  ReadString ();
  /*
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
