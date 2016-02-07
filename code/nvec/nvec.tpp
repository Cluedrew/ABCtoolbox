#ifndef ABCDEF_NVEC_TPP
#define ABCDEF_NVEC_TPP

#include <cstdarg>



namespace abc
{

template<typename ResultT,
         typename ArgT = ResultT,
         typename Alloc = std::allocator<T>>
std::vector<ResultT, Alloc> nvec(size_t const n, ...)
{
  std::vector<ResultT, Alloc> fin;
  fin.reserve(n);
  va_list args;

  try
  {
    va_start(args, n);
    for (size_t i = 0 ; i < n ; ++i)
      fin.push_back(ReturnT(va_arg(args, ArgT)));
    //fin.emplace_back(va_arg(args, ArgT));
  }
  catch (...)
  {
    va_end(args);
    throw;
  }

  va_end(args);
  return fin;
}
// Exceptions:
// std::length_error from reserve if n > fin.max_size()

/* This was the "motivating example" for this project and...
 *
 * std::vector<std::string> =
 *     nvec<std::string, char const *>(3, "rock", "paper", "spock");
 *
 * Well it is a bit ugly. So I'm trying for a short hand function variant.
template<typename Alloc = std::alloctor<std::string>>
std::vector<std::string,Alloc> nstrvec(size_t const n, ...)
{
  return nvec<std::string,char const *,Alloc>(n, ...);
}
 * Now the ... in the call probably will not work, but maybe I can get
 * around writing the whole thing out with:
typedef nvec<std::string,char const *,Alloc> nstrvec<Alloc>;
 * Although I'm almost positive that form will not work there may be one that
 * does. There may actually be no benefit (in code bloat) of only one
 * definition, in which case might as well define both manually.

template<typename Alloc = std::allocator<T>>
std::vector<std::string, Alloc> nstrvec(size_t const n, ...)
{
  std::vector<std::string, Alloc> fin;
  fin.reserve(n);
  va_list args;

  try
  {
    va_start(args, n);
    for (size_t i = 0 ; i < n ; ++i)
      fin.emplace_back(va_arg(args, char const *));
  }
  catch (...)
  {
    va_end(args);
    throw;
  }

  va_end(args);
  return fin;
}
 */

}

#endif//ABCDEF_NVEC_TPP
