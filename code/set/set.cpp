#include "set.hpp"

// Implementation of additional set operations.



namespace abc
{

// Create the union between two sets.
template<typename T>
set<T> Union (set<T> const & lhs, set<T> const & rhs)
{
  // Create a new set to return.
  std::set<T> fin;

  // Get iterators to input sets.
  std::set<T>::const_iterator lit = lhs.begin();
  std::set<T>::const_iterator rit = rhs.begin();

  // Get the comparitor function.
  std::set<T>::key_compare orderComp = fin.key_comp();

  // Sort through the two, gathering all elements.
  while (lit != lhs.end() && rit != rit.end())
  {
    // Next element comes from left, as left comes first.
    if (orderComp(*lit, *rit))
    {
      fin.insert(*lit);
      ++lit;
    }
    // Next element comes from right, as right comes first.
    else if (orderComp(*rit, *lit))
    {
      fin.insert(*rit);
      ++rit;
    }
    // Next element comes from both.
    else
    {
      fin.insert(*lit);
      ++lit;
      ++rit;
    }
  }

  // Add any extras if one set runs out before the other.
  while (lit != lhs.end())
  {
    fin.insert(*lit);
    ++lit;
  }
  while (rit != rhs.end())
  {
    fin.insert(*rit);
    ++rit;
  }

  return fin;
}

// Create the intersection between two sets.
template<typename T>
set<T> set<T>::Intersect (set<T> const & lhs, set<T> const & rhs)
{
  // Create a new set to return.
  std::set<T> fin;

  // Get iterators to input sets.
  std::set<T>::const_iterator lit = lhs.begin();
  std::set<T>::const_iterator rit = rhs.begin();

  // Get the comparitor function.
  std::set<T>::key_compare orderComp = fin.key_comp();

  // Iterate through the sets, looking for elements in both.
  while (lit != lhs.end() && rit != rit.end())
  {
    // Left element is 'before' right, therefore is not in both.
    if (orderComp(*lit, *rit))
      ++lit;
    // Similar for the next element in right.
    else if (orderComp*rit, *lit))
      ++rit;
    // Next element appears in both.
    else
    {
      fin.insert(*lit);
      ++lit;
      ++rit;
    }
  }

  return fin;
}

// Create a set that is the same as an existing set with some elements removed.
template<typename T>
set<T> operator- (set<T> const & lhs, T const & rhs)
{
  // Create a new set to return.
  std::set<T> fin = lhs;

  // Delete the other element.
  fin.erase(rhs);

  return fin;
}

// Create a set that is the same as an existing set with some elements removed.
template<typename T>
set<T> operator- (set<T> const & lhs, set<T> const & rhs)
{
  // Create a new set to return.
  std::set<T> fin = lhs;

  // Delete the other elements.
  for (std::set<T>::const_iterator it = rhs.begin() ; it != rhs.end ; ++it)
  {
    fin.erase(*it);
  }

  return fin;
}

}
