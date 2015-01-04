#ifndef ABCDEF_FF_SCANNER_BASE
#define ABCDEF_FF_SCANNER_BASE

/* This is the abstract base used by other the formated file functions.
 */


namespace abc
{
// Internal class:
class FFStaticBase;



class FFScannerBase
{
private:
  FFStaticBase * format;
  
protected:
  FFScannerBase & operator= (FFScannerBase const & other);
  
public:
  FFScannerBase ();
  FFScannerBase (std::string const & format);
  FFScannerBase (FFScannerBase const & other);
  
  virtual ~FFScannerBase() =0;
};

}

#endif//ABCDEF_FF_SCANNER_BASE
