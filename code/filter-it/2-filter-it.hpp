#ifndef FILTER_IT_HPP
#define FILTER_IT_HPP

// Scratch Pad Header.
/*
New idea, have an itermediate type of iterator 'container aware iterator' and
use that as a base of the filter_iterator. ... Is that any better than having
the interface? At some level there has to be the 'four versions' for the
different iterator versions.

What exactly does the interface have to do?
- Define the underlying iterator type (four types x container + ?)
- Define begin and end for the said iterator type.

Is the filter_iterator itself really an iterator? Yes I guess so it should
inherit from the iterator base class. But then where does it get its
properties? ... underlying_interface so that means... the
filter_interator_base doesn't actually use container_type itself, that is just
a short cut in the inherited stl_*_filter_iterator.

So the underlying_interface is just access to an iterator type and how to
start and end it. It can be any class that does that. Actually the stl
containers could probably be used directly, except you could only grab the
plain iterator (not constant_ / reverse_) and so there will be a few
converters for that.

That just leaves the filter. Which I am turnning into a template argument
because making an instance of a object is easier than writing out a new
function every time. I will probably write out and include a few classes that
can be used (such as one that checks for equality with its construtor argument
or one that is just a wrapper around a function pointer... or would you just
use the function pointer directly then?)
*/

namespace abc
{

// The base for the filter iterator
template<typename underlying_interface, typename filter_type = filter<T> >
class filter_iterator_base
                      // This will define all the iterators 'component' typedefs.
                      // Get from underlying_interface ? ( X typename underlying_interface::X ?)
    : public iterator<typename Category, // Limited to forward?
                      typename T,
                      typename Distance = ptrdiff_t,
                      typename Pointer = T*,
                      typename Reference = T&>
{
private:
  // Access to the underlying interator type
  typedef typename underlying_interface::iterator underlying_iterator;
  // The interface to the underlying iterator.
  underlying_interface uInter;
  // The filter instance, must have function bool(*)(value_type)
  filter_type filter;
  // The iterator we use itself.
  iterator it;
protected:
  // Advance in internal iterator (at least zero times) to reach a
  // non-filtered out item.
  void AdvanceZero ()
  {
     while (*it != uInter.end() && !filter(*it)) ++it;
  }
public:
  // I think it will inharite the category, value_type and so on from the
  // iterator type. Or do I have to do the round about thing that
  // reverse_iterator does? (Why else would they do it?)

  filter_iterator_base(
    underlying_interface uInterface = underlying_interface(),
    filter_type filter = filter_type()) :
      uInter(uInter), filter(filter), it(uInter.begin())
  {}
  // Constructor is all optional arguments. The iterator is default construtable if both
  // the underlying_interface and filter_type are.
  // Variant to give just the filter.
  filter_iterator_base(filter_type filter) :
      uInter(), filter(filter), it(uIter.begin())
  {}

  // ... stuff currantly in the main class ...
  /* TODO
  filter_iterator_base(filter_interator_base<underlying_interator,
                                             filter_type>          const & other)
  operator++()
  operator++(int)
  operator--() ?
  operator--(int) ?
  operator bool () ?
  operator! () ?
  */
}

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

  typedef typename container_type::iterator iterator;
  typedef typename container_type::value_type value_type;

  iterator begin(container_type cont)
  { return cont.begin(); }
  iterator end(container_type cont)
  { return cont.end(); }
}

// If I inhearit I would have to do from a base class without the defines.
// Which is the only thing I wouldn't have to re-define anyways. Skip.

// The other three stl container wrappers.
// They just 'wrap' on of the other kinds of iterators as a plain iterator.
// ... maybe I shouldn't call it 'iterator'... is that missleading?
//class stl_const_iterator_interface
//class stl_reverse_iterator_interface
//class stl_const_reverse_iterator_interface


// The absolute minimum should be in these classes.
// Infact they just be the class declaration and a construtor each ideally.
// An example specialization of an iterator
template<typename container_type, typename filter_type = filter<T> >
class stl_filter_iterator :
    public filter_interator_base<stl_iterator_interface<container_type>, filter>
{
  stl_filter_iterator(container_type & container, filter_type filter = filter_type()) :
      filter_iterator(stl_iterator_iterface(container), filter)
  {}

  // ... some stuff, the majority should be inherited ...
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

template<typename T>
struct filter
{
  // Filters out NULLs and 0s and so on.
  virtual bool operator() (T const & t) const
  { return bool(t); }
  typedef T argument_type;
  typedef bool result_type;
};

template<typename T>
struct equals_filter : public filter<T>
{
  T equals_to;
  equals_filter (T equals_to) : equals_to(equals_to) {}
  virtual bool operator() (T const & t) (const)?
  { return equals_to == t; }
};

}

#endif//FILTER_IT_HPP
