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
  static Terminal * GetInstance ();
};

}

#endif//ABCDEF_TERMINAL_H
