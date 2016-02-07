#ifndef ABCDEF_NVEC_HPP
#define ABCDEF_NVEC_HPP 1.0

// Provides a function template for creating a new vector.

#include <vector>



namespace abc
{
template<typename ResultT,
         typename ArgT = ResultT,
         typename Alloc = std::allocator<T>>
std::vector<ResultT,Alloc> nvec(size_t const n, ...);
/* Create a vector from containing the given arguments.
 * Params: First is n, the size of vector. This should be followed by exactly
 *   n additional parameters of ArgT.
 * Effect: Allacates a new vector.
 * Return: A new vector of size n, created with copies (converted if nessasry)
 *   of the trailing parameters in order.
 * Throws: May throw if there is no space or construction of an element fails.
 *   Has a strong gerenty as long as the allocator can construct and free
 *   ResultT.
 *
 * ResultT: The value_type, of the returned vector.
 * ArgT: The type of the provided argument. ResultT must construct from ArgT.
 * AllocT: If a non-standard allocator is used, provide it here.
 */
}

#include <nvec.tpp>

#endif//ABCDEF_NVEC_HPP
