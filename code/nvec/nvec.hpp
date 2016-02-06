#ifndef ABCDEF_NVEC_HPP
#define ABCDEF_NVEC_HPP 1.0

// Provides a function template for creating a new vector.

#include <vector>



namespace abc
{
template<typename ResultT, typename ArgT = ResultT>
std::vector<ResultT> nvec(size_t const n, ...);
/*
 * Params:
 * Effect:
 * Return:
 * Throws:
 */
}

#include <nvec.tpp>

#endif//ABCDEF_NVEC_HPP
