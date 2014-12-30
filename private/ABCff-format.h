#ifndef ABCDEF_FF_FORMAT_H
#define ABCDEF_FF_FORMAT_H

// The format of a file that FFScanner will read from.

#include <string>



namespace abc
{
enum class FFTokenType {word, line};

class FFFormat
{
private:
  int uses;
  std::string format;
  
protected:
public:
  FFFormat (std::string &);
  
  virtual ~FFFormat ();
  
  void UseThis();
  /* Adds to the number of uses of this FFFormat.
   * Prams.: void
   * Effect: This will remember the additional use.
   * Return: void
   */
  
  bool StopUse();
  /* Decreases the number of uses of this and return if it is now unused.
   * Prams.: void
   * Effect: This will have less uses.
   * Return: If there are no more active uses will return true and this should
   *    then be deleted, otherwise returns false and this should remain.
   */
}

}

#endif//ABCDEF_FF_FORMAT_H
