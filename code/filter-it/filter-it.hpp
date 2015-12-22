#ifndef FILTER_IT_HPP
#define FILTER_IT_HPP

/* Filter iterator class templates and related definitions.
 *
 * filter_iterator_base:
 *
 * stl*iterator_interface:
 *
 * stl*filter_iterator:
 *
 * *filter:
 */

#include <iterator>

namespace abc
{

// The base for the filter iterator
template<typename base_interface, typename filter_type = filter<T> >
class filter_iterator_base
    : public iterator<typename Category, // Limited to forward?
                      typename base_interface::value_type,
                      typename Distance = ptrdiff_t, // Default?
                      typename Pointer = T*, // Default?
                      typename Reference = T&> // Default?
{
public:
  // Access to the underlying interator type.
  // One name that makes sense, one to match the stl.
  typedef typename base_interface::iterator_type iterator_type;
  typedef typename base_interface::iterator_type base_iterator;

private:
  // The interface to the underlying iterator.
  base_iterator baseInter;
  // The filter instance, must have function bool(*)(value_type)
  filter_type filter;
  // The iterator we use itself.
  base_iterator it;

protected:
  // Advance in internal iterator (at least zero times) to reach a
  // non-filtered out item.
  void advanceZero ()
  {
    while (it != baseInter.end() && !filter(*it)) ++it;
  }

  // Advance the internal iterator (at least one time) to reach a
  // non-filtered out item.
  void advanceOne ()
  {
    do ++it
    while (it != baseInter.end() && !filter(*it));
  }

  // Advance the iterator in the other direction (at least once) to reach a
  // non-filtered out item. Except when we are already at the beginning, then
  // don't move the iterator.
  void retreatOne ()
  {
    if (it != baseInter.begin())
      do --it
      while (it != baseInter.begin() && !filter(*it));
  }

public:
  // I think it will inharite the category, value_type and so on from the
  // iterator type. Or do I have to do the round about thing that
  // reverse_iterator does? (Why else would they do it?)

  filter_iterator_base(
    base_interface baseInter = base_interface(),
    filter_type filter = filter_type()) :
      baseInter(baseInter), filter(filter), it(baseInter.begin())
  { advanceZero(); }
  // Constructor is all optional arguments. The iterator is default construtable if both
  // the underlying_interface and filter_type are.
  // Variant to give just the filter.
  filter_iterator_base(filter_type filter) :
      baseInter(), filter(filter), it(baseIter.begin())
  { advanceZero(); }

  // Dereference Operator
  value_type & operator* ()
  {
    return it.operator*();
  }

  // Member Dereference Operator
  value_type * operator-> ()
  {
    return it.operator->();
  }

  // Pre-Increment Operator
  filter_iterator<base_interface, filter_type> & operator++ ()
  {
    advanceOne();
    return *this;
  }

  // Post-Increment Operator
  filter_iterator<base_interface, filter_type> operator++ (int)
  {
    filter_iterator<base_interface, filter_type> tmp = *this;
    advanceOne();
    return tmp;
  }

  // Pre-Decrement Operator
  filter_iterator<base_interface, filter_type> & operator-- ()
  {
    retreatOne();
    return *this;
  }

  // Post-Decrement Operator
  filter_iterator<base_interface, filter_type> operator-- (int)
  {
    filter_iterator<base_interface, filter_type> tmp = *this;
    retreatOne();
    return tmp;
  }

  // Boolean Conversion (is valid)
  operator bool () const
  {
    return it != baseInter.end();
  }

  // Boolean Negation (is invalid)
  bool operator! () const
  {
    return it == baseInter.end();
  }

  // baseInter Member Access
  base_interface & getInterface ()
  {
    return baseInter;
  }

  base_interface const & getInterface () const
  {
    return baseInter;
  }

  // filter Member Access
  filter_type & getFilter ()
  {
    return filter;
  }

  filter_type const & getFilter () const
  {
    return filter;
  }
}

// STL Iterator Options ======================================================

// A type that implements the nessary interface operations.
template<container_type>
class stl_iterator_interface
{
private:
  container_type & cont;
protected:
public:
  stl_iterator_interface(container_type & container) :
      cont(container)
  {}

  typedef typename container_type::iterator iterator_type;
  typedef typename container_type::iterator_catagory iterator_catagory;
  typedef typename container_type::value_type value_type;

  // Container's begin.
  iterator_type begin(container_type cont)
  { return cont.begin(); }

  // Container's end.
  iterator_type end(container_type cont)
  { return cont.end(); }

  // Are these supposed to be taking arguments? I can't remember.
}

// The other three stl container wrappers. They do the same as above except
// with one of the other three standard iterators
//class stl_const_iterator_interface
//class stl_reverse_iterator_interface
//class stl_const_reverse_iterator_interface


// The absolute minimum should be in these classes.
// Infact they just be the class declaration and a construtor each ideally.
// An example specialization of an iterator
template<typename container_type, typename filter_type = filter<T> >
class stl_filter_iterator :
    public filter_interator_base<stl_iterator_interface<container_type>,
                                 filter_type>
{
  stl_filter_iterator(container_type & container, filter_type filter = filter_type()) :
      filter_iterator_base(stl_iterator_iterface(container), filter)
  {}
}

/*
template <typename Category, typename T, typename Distance = ptrdiff_t,
          typename Pointer = T*, typename Reference = T&>
struct iterator
{
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
  typedef Category  iterator_catagory;
};
*/

// Provided Filter Types =====================================================

template<typename T>
struct filter
{
  // Filters out NULLs and 0s and so on.
  virtual bool operator() (T const & t) const
  { return bool(t); }
  typedef T argument_type;
  typedef bool result_type;
};

template<typename T/*, typename commaritor = equal_to<T> */>
struct equals_filter : public filter<T>
{
  T equals_to;
  equals_filter (T equals_to) : equals_to(equals_to) {}
  virtual bool operator() (T const & t) (const)?
  { return equals_to == t; }
};

template<typename T>
struct func_filter : public filter<T>
{
  bool (*func) (T const &);
  func_filter (bool(*func)(T const &)) : func(func) {}
  virtual bool operator() (T const & t) const
  { return func(t); }
};

/* Should I seperate this out more? They don't in the stl but I would like
 * my documentation to be readable.
 */

// Interface =================================================================
// ===========================================================================
// Implementation ============================================================

// inline functions for the above declarations.
#define BASE_TEMPLATE_HEAD(return_type) \
template<typename base_interface, typename filter_type> \
inline return_type filter_interator_base<base_interface, filter_type>

#undef BASE_TEMPLATE_HEAD

// Advance in internal iterator (at least zero times) to reach a
// non-filtered out item.
template<typename base_interface, typename filter_type>
void filter_iterator_base<base_interface, filter_type>::advanceZero ()
{
  while (it != baseInter.end() && !filter(*it)) ++it;
}

// Advance the internal iterator (at least one time) to reach a
// non-filtered out item.
template<typename base_interface, typename filter_type = filter<T> >
void filter_iterator_base<base_interface, filter_type>::advanceOne ()
{
  do ++it
  while (it != baseInter.end() && !filter(*it));
}

// Advance the iterator in the other direction (at least once) to reach a
// non-filtered out item. Except when we are already at the beginning, then
// don't move the iterator.
template<typename base_interface, typename filter_type = filter<T> >
void filter_iterator_base<base_interface, filter_type>::retreatOne ()
{
  if (it != baseInter.begin())
    do --it
    while (it != baseInter.begin() && !filter(*it));
}

template<typename base_interface, typename filter_type = filter<T> >
class filter_iterator_base

}

#endif//FILTER_IT_HPP
