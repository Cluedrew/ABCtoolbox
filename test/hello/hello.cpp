/*
Call the hello world tool.
Like the hello world tool itself this is more for testing the system rather
than the tool itself. Because the hello world tool is supper simple.

Can't compil it.
g++ test/hello/hello.cpp -L/usr/local/include/ABC -lhello-world -o test/hello/hello
*/

#include <ABC/hello-world.hpp>

int main (int argc, char * argv[])
{
  abc::HelloWorld();
  return 0;
}
