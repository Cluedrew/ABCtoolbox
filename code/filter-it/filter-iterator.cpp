#include "filter-iterator.hpp"

// Implementation of the FilterIterator.
// Will later be converted to a epp/tpp file
//   and included from the header (template).

// I'm leaving in the ';' or purpose until I'm actually sure these might work.

namespace abc
{

// template<typename ContainerT_> FilterIterator<ContainerT_>::

/* Does this work in any way?
typedef template<typename ContainerT_> FilterInterator<ContainerT_>
        ThisFilterIterator;
*/

// Constructors, Deconstructor and Assignment ================================

// Full Constructor
template<typename ContainerT_>
FilterIterator<ContainerT_>::FilterIterator
    (ContainerT_ * container, filter_type filter); :
  container(...), it(...), filter(...)
{}

// Default Constructor (req)
template<typename ContainerT_>
FilterIterator<ContainerT_>::FilterIterator ();

// Copy Constructor (req)
template<typename ContainerT_>
FilterIterator<ContainerT_>::FilterIterator (FilterIterator const & other);

// Deconstructor (req)
template<typename ContainerT_>
FilterIterator<ContainerT_>::~FilterIterator();

// Copy Assignment (req)
template<typename ContainerT_>
FilterIterator & FilterIterator<ContainerT_>::operator=
    (FilterIterator const & other);

// Move Constrctor
template<typename ContainerT_>
FilterIterator<ContainerT_>::FilterIterator (FilterIterator const && other);

// Move Assignment
template<typename ContainerT_>
FilterIterator & FilterIterator<ContainerT_>::operator=
    (FilterIterator const && other);
{}

// Increments and Decrements =================================================
// The implementation of ++/-- is were the filter actually happens.

// Pre-Increment (req)
template<typename ContainerT_>
FilterIterator & FilterIterator<ContainerT_>::operator++ ();

// Post-Increment (req)
template<typename ContainerT_>
FilterIterator & FilterIterator<ContainerT_>::operator++ (int);

// Pre-Decrement (req)
template<typename ContainerT_>
FilterIterator & FilterIterator<ContainerT_>::operator-- ();

// Post-Decrement (req)
template<typename ContainerT_>
FilterIterator & FilterIterator<ContainerT_>::operator-- (int);

// Dereferencing Operators ===================================================
// I think these just mimic the underlying iterator.

// Dereference (req)
template<typename ContainerT_>
value_type & FilterIterator<ContainerT_>::operator* ();

// Member Dereference (req)
template<typename ContainerT_>
value_type * FilterIterator<ContainerT_>::operator-> ();

// Predicate Functions =======================================================

// Equality Check
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::operator== (FilterIterator const & other);

// Inequality Check
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::operator!= (FilterIterator const & other);

// In Range Check
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::isValid ();

// Out of Range Check
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::isInvalid ();

// Type Conversions ==========================================================

// In Range Check (?)
template<typename ContainerT_>
FilterIterator<ContainerT_>::operator bool ();

// Out of Range Check (?)
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::operator! ();

// Member Access (Get/Set) ===================================================

// For the default constructor we will need ways to change the container
// and the filter.
template<typename ContainerT_>
void FilterIterator<ContainerT_>::update_container (ContainerT_ * container);
template<typename ContainerT_>
void FilterIterator<ContainerT_>::update_filter (filter_type filter);

}// namespace abc

#endif//FILTER_ITERATOR_HPP
