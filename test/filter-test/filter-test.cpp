/* Primary testing unit for the Filter Iterator class.
 */

#include <ABC/filter-it.hpp>
using abc::FilterIterator;

#include <iostream>

// How well does it iterate through some stl containers?
#include <vector>
#include <map>
#include <set>

// ----- Filter functions
// Is the given number even?
bool isEven (int const & n)
{ return (0 == n % 2); }

// Is the key (first) even?
bool isKeyEven (std::pair<const int, char> const & p)
{ return (0 == p.first % 2); }

// ----- Tests
// Run a basic test, using the FilterIterator on a vector, print results.
void testVector ()
{
  std::vector<int> vec;
  // Fill the vector [0..9].
  for (int i = 0 ; i < 10 ; ++i)
    vec.push_back(i);

  // Print out all even numbers in the vector.
  std::cout << "Test Vector:" << std::endl;
  for (FilterIterator<std::vector<int> > fit(vec, isEven) ; (bool)fit ; ++fit)
    std::cout << *fit << ',';
  std::cout << std::endl;
}

// Run a test using the FilterIterator and a set, print results.
void testSet ()
{
  std::set<int> set;
  // Fill the set [0..9].
  for (int i = 0 ; i < 10 ; ++i)
    set.insert(i);

  // Print out all even numbers in the set.
  std::cout << "Test Set:" << std::endl;
  for (FilterIterator<std::set<int> > fit(set, isEven) ; (bool)fit ; ++fit)
    std::cout << *fit << ',';
  std::cout << std::endl;
}

// Run a test uning the FilterIterator and a map, print results.
void testMap ()
{
  std::map<int, char> map;
  // Fill the set [0..9].
  for (int i = 0 ; i < 10 ; ++i)
    map.insert(std::pair<int, char>(i, (char)(i + 'a')));

  // Print out all even numbers in the set.
  std::cout << "Test Map:" << std::endl;
  for (FilterIterator<std::map<int, char> > fit(map, isKeyEven)
      ; (bool)fit ; ++fit)
    std::cout << '(' << fit->first << ',' << fit->second << ')';
  std::cout << std::endl;
}

int main (int argc, char * argv[])
{
  testVector();
  testSet();
  testMap();
  return 0;
}
