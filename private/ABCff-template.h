#ifndef ABCDEF_FF_TEMPLATE_H
#define ABCDEF_FF_TEMPLATE_H

// Create a template from which to build FFScanners.

#include <string>



namespace abc
{
class FFFormat;



class FFTemplate
{
private:
  FFFormat * format;
  
protected:
public:
  FFTemplate (char const * formatString);
  FFTemplate (std::string);
  
  virtual ~FFTemplate ();
}

}

#endif//ABCDEF_FF_TEMPLATE_H
