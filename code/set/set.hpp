#ifndef ABCDEF_SET_HPP
#define ABCDEF_SET_HPP

/* Avanced set functions. It implements some set operation missed in the STL
 * (such as Union and Intersect) and adds some operator overloads for some
 * others (-).
 *
 * It should work, but I still have to test it. Then maybe I should optomize
 * the code somewhat (hints might help).
 */

namespace abc
{

// Import and rename the standard set.
#include <set>
typedef std::set set;



template<typename T>
set<T> Union (set<T> const &, set<T> const &);
/* Create the union between two sets.
 * Params: Two sets to find the union with.
 * Effect: void
 * Return: The resulting union between two sets.
 */

template<typename T>
set<T> Intersect (set<T> const &, set<T> const &);
/* Create the intersection between two sets.
 * Params: Two sets to find the intersection between.
 * Effect: void
 * Return: The resulting intersection between two sets.
 */

template<typename T>
set<T> operator- (set<T> const &, T const &);
template<typename T>
set<T> operator- (set<T> const &, set<T> const &);
/* Create a set that is the same as an existing set with some elements removed.
 * Params: The left hand side is a set, the right hand side is either a set or
 *    a single element.
 * Effect: void
 * Return: A new set that contains every element from the left hand set not
 *    equal to (or containing within) the right hand side.
 * Note: If the LHS is a set represting the universal set than A-B will give
 *    B's complement.
 */
}

#endif//ABCDEF_SET_HPP
