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
template<typename container_type, typename underlying_interface, typename filter_type = filter<T> >
class filter_iterator_base
                      // This will define all the iterators 'component' typedefs.
                      // Get from underlying_interface ? ( X typename underlying_interface::X ?)
    : public iterator<typename Category,
                      typename T,
                      typename Distance = ptrdiff_t,
                      typename Pointer = T*,
                      typename Reference = T&>
{
public:
  // Access to the underlying interator type
  typedef typename underlying_interface::iterator underlying_iterator;
private:
protected:
public:
  // ... stuff currantly in the main class ...
}

// A type that implements the nessary interface operations.
template<container_type>
struct stl_iterator_interface
{
  typedef typename ContainerT_::iterator iterator;
  underlying_iterator beginning(ContainerT_ cont)
  { return cont.begin(); }
  underlying_iterator ending(ContainerT_ cont)
  { return cont.end(); }
}

// An example specialization of an iterator
template<typename container_type, typename filter = filter<T> >
class stl_filter_iterator :
    public filter_interator_base<container_type, stl_iterator_interface<container_type>, filter>
{
private:
  // Should be a reference or pointer.
  container_type cont;
protected:
public:
  stl_filter_iterator(container_type container) :
      cont(container)
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
  virtual bool operator() (T const &) (const)? {...}
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
