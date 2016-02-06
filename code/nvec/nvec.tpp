#ifndef ABCDEF_NVEC_TPP
#define ABCDEF_NVEC_TPP

#include <cstdarg>



namespace abc
{

template<typename ResultT, typename ArgT = ResultT>
std::vector<ResultT> nvec(size_t const n, ...)
{
  std::vector fin;
  va_list args;

  try
  {
    va_start(args, n);
    for (size_t i = 0 ; i < n ; ++i)
      fin.push_back(ResultT(va_arg(args, ArgT)));
  }
  catch (...)
  {
    va_end(args);
    throw;
  }
  va_end(args);
  return fin;
}

}

#endif//ABCDEF_NVEC_TPP
