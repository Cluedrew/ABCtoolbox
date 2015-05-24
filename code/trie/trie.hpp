#ifndef TRIE_HPP
#define TRIE_HPP

// My latest attempty to built an online trie/suffix tree
// with Ukkonen's algorithum. Success has been mixed.

#include <vector>

// I think I will be using this (make it a private, static member),
// When I can figure out how.
#include <limit>
int const INT_INF = std::numeric_limits<int>::max();



// The main class that acts as a wrapper to all others.
class Trie
{
private:
  std::vector<char> chs;
protected:
public:
  Trie();
  Trie(char *);

  virtual ~Trie ()

  int StrLength();
  // Length of the string it is a try off.

  void append (char);
};

// A node and the range of the edge leading to it.
class TrieNode
{
private:
  // The indexes of the first and last characters on the edge.
  int first;
  int last;
protected:
public:
  TrieNode ();

  virtual ~TrieNode ();
};

// Blup:
class TrieBranching;
/* Possibly will need this class to be the destination of suffix links.
 * Will probably have some traversal related things in it because that is
 * both shared by all things that should be using it and because that is what
 * we want (?) to find when we have traversed it.
 */

/*
  For a sting S, length n, the algorthum fills in every substring S[j..n] by
filling in every S[j..i] for i 1..n. (When we get to the implemention it will
be 0..n-1, but we will use this for theory right now.)
  So it counts from 1 to n over i and each step goes from 1 to i over j. With
a regular try each step would take j traversals or so giving a cubic runtime.
Various tricks speed this up.
  One such trick is that the trie uses index numbers instead of the actual
characters (which also saves space) to store the range of the original string
S the edge covers. Also it doesn't store "end" characters or nodes that only
show a suffix ends.
  Leaves will always have their last edge on i, where i is the index of the
last character. Leaves can also store the index of the first character of the
suffix, it's in a lot of diagrams but is not needed.
There are internal pointers (I think) between internal nodes with the same
shape of children. These can point to but not from the root.
  Construction is divided into phases (i=1..n) and each phase is divided
into extentions (j=1..i). The algorithum can stop an the end of each phase
(or should be abile to) and to other things will it waits for the next
charater.
  There are tree ways extentions can occure:
At a leaf (implicate with the unset leave end).
In the tree branching off of the existing structure.
In the tree on the existing structure (nothing to be done).
*/

#endif//TRIE_HPP
