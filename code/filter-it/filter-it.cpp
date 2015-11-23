#include "filter-it.hpp"

// Implementation of the FilterIterator.
// Will later be converted to a epp/tpp file
//   and included from the header (template).

#include <stdexcept>

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
    (ContainerT_ * container, filter_type filter) :
  container(container), it(container.begin()), filter(filter)
{
  // If the beginning element is filtered out, move onto one that is not.
  if (!filter(*it))
     this->operator++();
}
// Identical Full Constructor, except this one handles the derefencing.
template<typename ContainerT_>
FilterIterator<ContainerT_>::FilterIterator
    (ContainerT_ & container, filter_type filter) :
  container(&container), it(container.begin()), filter(filter)
{
  // If the beginning element is filtered out, move onto one that is not.
  if (!filter(*it))
     this->operator++();
}

// Default Constructor (req)
//template<typename ContainerT_>
//FilterIterator<ContainerT_>::FilterIterator () :
//  container(nullptr), it(), filter(nullptr)
//{}

// Copy Constructor (req)
template<typename ContainerT_>
FilterIterator<ContainerT_>::FilterIterator
    (FilterIterator<ContainerT_> const & other) :
  container(other.container), it(other.it), filter(other.filter)
{}

// Deconstructor (req)
template<typename ContainerT_>
FilterIterator<ContainerT_>::~FilterIterator()
{
  // Currantly, the FilterIterator does not actually claim the memory for
  // the container object, the internal iterator or the filter.
}

// Copy Assignment (req)
template<typename ContainerT_>
FilterIterator<ContainerT_> & FilterIterator<ContainerT_>::operator=
    (FilterIterator<ContainerT_> const & other)
{
  container = other.container;
  it = other.it;
  filter = other.filter;
}

// Move Constrctor
//template<typename ContainerT_>
//FilterIterator<ContainerT_>::FilterIterator
//    (FilterIterator<ContainerT_> && other) :
//  container(other.container), it(other.it), filter(other.filter)
//{}

// Move Assignment
//template<typename ContainerT_>
//FilterIterator<ContainerT_> & FilterIterator<ContainerT_>::operator=
//    (FilterIterator<ContainerT_> && other)
//{
//  container = other.container;
//  it = other.it;
//  filter = other.filter;
//}

// Increments and Decrements =================================================
// The implementation of ++/-- is were the filter actually happens.

// Pre-Increment (req)
template<typename ContainerT_>
FilterIterator<ContainerT_> & FilterIterator<ContainerT_>::operator++ ()
{
  do ++it;
  while (!filter(*it) && it != container.end());
  return *this;
}

// Post-Increment (req)
template<typename ContainerT_>
FilterIterator<ContainerT_> FilterIterator<ContainerT_>::operator++ (int)
{
  FilterIterator<ContainerT_> tmp = *this;
  do ++it;
  while (!filter(*it) && it != container.end());
  return tmp;
}

// Pre-Decrement (req)
template<typename ContainerT_>
FilterIterator<ContainerT_> & FilterIterator<ContainerT_>::operator-- ()
{
  do --it;
  while (!filter(*it) && it != container.begin());
  return *this;
}

// Post-Decrement (req)
template<typename ContainerT_>
FilterIterator<ContainerT_> FilterIterator<ContainerT_>::operator-- (int)
{
  FilterIterator<ContainerT_> tmp = *this;
  do --it;
  while (!filter(*it) && it != container.begin());
  return tmp;
}

// Dereferencing Operators ===================================================
// I think these just mimic the underlying iterator.

// Dereference (req)
template<typename ContainerT_>
typename FilterIterator<ContainerT_>::value_type &
    FilterIterator<ContainerT_>::operator* ()
{
  return it.operator*();
}

// Member Dereference (req)
template<typename ContainerT_>
typename FilterIterator<ContainerT_>::value_type *
    FilterIterator<ContainerT_>::operator-> ()
{
  return it.operator->();
}

// Predicate Functions =======================================================

// Equality Check
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::operator== (FilterIterator const & other)
{
  return container == other.container &&
         it == other.it &&
         filter == other.filter;
}

// Inequality Check
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::operator!= (FilterIterator const & other)
{
  return container != other.container ||
         it != other.it ||
         filter != other.filter;
}


// In Range Check
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::isValid ()
{
  return it != container.end() && it != container.rend();
}

// Out of Range Check
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::isInvalid ()
{
  return it == container.end() || it == container.rend();
}

// Type Conversions ==========================================================

// In Range Check (?)
template<typename ContainerT_>
FilterIterator<ContainerT_>::operator bool ()
{
  return isValid();
}

// Out of Range Check (?)
template<typename ContainerT_>
bool FilterIterator<ContainerT_>::operator! ()
{
  return isInvalid();
}

// Member Access (Get/Set) ===================================================

// For the default constructor we will need ways to change the container
/*/ and the filter.
template<typename ContainerT_>
void FilterIterator<ContainerT_>::update_container (ContainerT_ * container);
template<typename ContainerT_>
void FilterIterator<ContainerT_>::update_filter (filter_type filter);
//*/
}// namespace abc
