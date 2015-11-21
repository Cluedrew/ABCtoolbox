#ifndef FILTER_ITERATOR_HPP
#define FILTER_ITERATOR_HPP

// WIP: I generally don't like iterators and don't know tones about them.

/* The filter iterator is a forward iterator that ignores some elements.
 * or it might be a bidirectional operator.
 * Either way I am trying to built it as close to the C++ standard as possible
 * so it fits in. Because of its nature that may not be possible in every case
 * but I will try.
 *
 * It should work with most containers in the standard template library, or
 * and container that implements:
 * - value_type local typedef as the type of the elements in the container.
 * - const_reference local typedef as ... through allocator<>
 * - iterator local typedef as the type of a forward/bidirection iterator.
 */

template<typename ContainerT_>
class FilterIterator
{
public:
  typedef ContainerT_::value_type value_type;
  typedef bool (*filter_type)(ContainerT_::const_reference);
private:
  // Reference to underlying container.
  ContainerT_ & container;

  // The underlying iterator.
  ContainerT_::iterator it;

  // The value of the filter function.
  filter_type filter;
protected:
public:
  FilterIterator (ContainerT_ & container, filter_type filter);

  // Required constructors / deconstrctor
  FilterIterator ();
  FilterIterator (FilterIterator const & other);
  virtual ~FilterIterator();
  // Required copy-assignment
  FilterIterator & operator= (FilterIterator const & other);

  // Move constrctor and move-copy
  FilterIterator (FilterIterator const && other);
  FilterIterator & operator= (FilterIterator const && other);

  // More Required operators.
  // increment and decrament
  operator++ (); // pre
  operator++ (int); // post
  operator-- ();
  operator-- (int);
  operator== ();
  operator!= ();

  // dereference and member dereference
  operator* ();
  operator-> ();

  // In range check
  // short hand for end checks since this iterator might be container aware.
  bool isValid ();
  bool isInvalid ();
};

#endif//FILTER_ITERATOR_HPP
