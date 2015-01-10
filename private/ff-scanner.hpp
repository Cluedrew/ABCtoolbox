#ifndef ABCDEF_FF_SCANNER_HPP
#define ABCDEF_FF_SCANNER_HPP

/* This is the formated file scanner.
 */

#include <string>
#include <ifstream>



namespace abc
{
class FFStaticBase;



class FFScanner
{
private:
  FFStaticBase * format;
  std::ifstream file;
  unsigned int position;
  
  // Consiter added some "access wrappers".
  // char FChar(int at);
  
protected:
  FFScanner & operator= (FFScanner const & other);
  
public:
  FFScanner (std::string const & format);
  FFScanner (FFScanner const & other);
  
  //FFScanner (std::string const & format, std::string const & file);
  //FFScanner (FFScannerBase const & other, std::string const & file);
  
  virtual ~FFScanner();
  
  // static bool CheckFormat(std::string const & format);
  /* Make sure that ther
   * Prams.: A string containing a file format.
   * Effect: void
   * Return: True if the format is valid, false otherwise.
   */
  
  
  
  bool Open(std::string file);
  /* 
   * Prams.:
   * Effect:
   * Return:
   */
  
  void Close();
  /* 
   * Prams.:
   * Effect:
   * Return:
   */
  
  bool Check(std::string file);
  /* Check to see if the given file matches the format of this scanner.
   * Prams.:
   * Effect:
   * Return:
   */
  
  // Extraction Operator Overloads
  FFScanner & operator>> (char const &);
  FFScanner & operator>> (char const *);
  FFScanner & operator>> (std::string);
  /* These can be used to move forward in the format.
   * Prams.:
   * Effect:
   * Return:
   */
  
  //bool operator bool ();
  
  //void Clear(); clear error flags.
};

}

#endif//ABCDEF_FF_SCANNER_HPP
