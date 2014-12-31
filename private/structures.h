#ifndef ABCDEF_STRUCTURES_H
#define ABCDEF_STRUCTURES_H

// Simple structures used by the ABC Tool Box.



namespace abc
{
// location structure:
struct loc
{
  int x;
  int y;
  
  int R() {return y;}
  int C() {return x;}
};

// frame structure:
struct frame
{
  int x;
  int y;
  int w;
  int h;
  
  int R() {return y;}
  int C() {return x;}
};

}

#endif//ABCDEF_STRUCTURES_H
