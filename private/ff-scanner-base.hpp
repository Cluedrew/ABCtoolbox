#ifndef ABCDEF_FF_SCANNER_BASE_HPP
#define ABCDEF_FF_SCANNER_BASE_HPP

/* This is the abstract base used by other the formated file functions.
 */

#include <string>



namespace abc
{
class FFStaticBase;



class FFScannerBase
{
private:
  FFStaticBase * format;
  
protected:
  FFScannerBase & operator= (FFScannerBase const & other);
  
public:
  FFScannerBase (std::string const & format);
  FFScannerBase (FFScannerBase const & other);
  
  //FFScannerBase (std::string const & format, std::string const & file);
  //FFScannerBase (FFScannerBase const & other, std::string const & file);
  
  virtual ~FFScannerBase() =0;
};

}

#endif//ABCDEF_FF_SCANNER_BASE_HPP
