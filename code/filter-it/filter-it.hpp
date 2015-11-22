#ifndef FILTER_ITERATOR_HPP
#define FILTER_ITERATOR_HPP

// WIP: I generally don't like iterators and don't know tones about them.

/* Important: Currantly the defualt constructor creates an invalid object
 * that you can't really fix. The update functions and some checks will be
 * needed to fix that.
 */

/* The filter iterator is a forward iterator that ignores some elements.
 * or it might be a bidirectional operator. Unless I can fined a really clean
 * way to do it I'm probably not going to have the four types of iterators.
 *
 * Either way I am trying to built it as close to the C++ standard as possible
 * so it fits in. Because of its nature that may not be possible in every case
 * but I will try.
 *
 * Features for required for the standard are marked with (req).
 *
 * It should work with most containers in the standard template library, or
 * and container that implements:
 * - value_type local typedef as the type of the elements in the container.
 * - const_reference local typedef as ... through allocator<>
 * - iterator local typedef as the type of a forward/bidirection iterator.
 */

namespace abc
{

template<typename ContainerT_>
class FilterIterator
{
public:
  typedef typename ContainerT_::value_type value_type;
  typedef bool (*filter_type)(typename ContainerT_::const_reference);
private:
  // Reference to underlying container.
  ContainerT_ * container;

  // The underlying iterator.
  typename ContainerT_::iterator it;

  // The value of the filter function.
  filter_type filter;
protected:
public:
  // Full Constructor
  FilterIterator (ContainerT_ * container, filter_type filter);

  // Default Constructor (req)
  FilterIterator ();
  // Copy Constructor (req)
  FilterIterator (FilterIterator const & other);
  // Deconstructor (req)
  virtual ~FilterIterator();
  // Copy Assignment (req)
  FilterIterator & operator= (FilterIterator const & other);

  // Move Constrctor
  FilterIterator (FilterIterator const && other);
  // Move Assignment
  FilterIterator & operator= (FilterIterator const && other);

  // Pre-Increment (req)
  FilterIterator & operator++ ();
  // Post-Increment (req)
  FilterIterator operator++ (int);
  // Pre-Decrement (req)
  FilterIterator & operator-- ();
  // Post-Decrement (req)
  FilterIterator operator-- (int);

  /* About RunTime:
   *   Most iterators preform ++/-- in O(1) time. Because of the additional
   * logic covered by this iterator it will take at least O(n * O(f))
   * where n is the number of elements passed over (at least one but could be
   * the entire container) and O(f) is the execution time of the filter
   * predicate.
   *   However this is no slower than checking each element and incrementing
   * until we find a non-filtered out item, the operation it encasulates.
   */


  // Equality Check
  bool operator== (FilterIterator const & other);
  // Inequality Check
  bool operator!= (FilterIterator const & other);

  // Dereference (req)
  value_type & operator* ();
  // Member Dereference (req)
  value_type * operator-> ();

  // For the default constructor we will need ways to change the container
  // and the filter. (Not implemented.)
  void update_container (ContainerT_ * container);
  void update_filter (filter_type filter);

  // In range check
  // short hand for end checks since this iterator might be container aware.
  bool isValid ();
  bool isInvalid ();

  // In Range Check (?)
  operator bool ();
  // Out of Range Check (?)
  bool operator! ();

  // Possibly some type conversions to and from other types of iterators.
  // Or at least the "base" iterator.
};

}

#endif//FILTER_ITERATOR_HPP
