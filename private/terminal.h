#ifndef ABCDEF_TERMINAL_H
#define ABCDEF_TERMINAL_H

/* The termainal class allows for grid based use of consol, instead of the
 * command line style it usually has.
 */



namespace abc
{
class Termainal
{
private:
  Termainal * instance;
  
  Termainal ();
  
protected:
public:
  virtual ~Termainal ();
  
  static bool CreateTermainal ();
  
  static Termainal * GetInstance ();
};

}

#endif//ABCDEF_TERMINAL_H
