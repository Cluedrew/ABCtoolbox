#ifndef FILTER_ITERATOR_HPP
#define FILTER_ITERATOR_HPP

/* The FilterIterator is a special iterator that ignores functions that to not
 * pass a predicate test. It is almost a Bidirectional iterator, lacking only
 * the default constructor.
 *
 * WIP: Bugs and limitations are abound, but it should work in most simple
 * cases.
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
  //FilterIterator ();
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
