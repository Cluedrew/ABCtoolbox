#ifndef ABC_DEFINE_H
#define ABC_DEFINE_H 1.0

// Preprocesser defines

#define ABCDEF_STR(s) #s

#define ABCDEF_PATH(d) ../code/ ## d
/* Is meant to be with includes, two examples.
 * #include "ABCDEF_PATH(.)/header.hpp"
 * #include "ABCDEF_PATH(subdir)/header.hpp
 */

#endif//ABC_DEFINE_H
