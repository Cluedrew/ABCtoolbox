#ifndef ABCDEF_FF_STATIC_BASE_HPP
#define ABCDEF_FF_STATIC_BASE_HPP

/* The static base class holds within it all the infromation that is shared
 * between instances of a scanner that have the same format.
 */

#include <string>



namespace abc
{
class FFStaticBase
{
  // The class is completely private, only allowing FFScanner to use it.
  friend class FFScanner;
  
  int uses;
  std::string const format;
  
  FFStaticBase (std::string const & format_);
  
  // The deconstructor is the only public member.
public:
  ~FFStaticBase ();
};

}

#endif//ABCDEF_FF_STATIC_BASE_HPP
