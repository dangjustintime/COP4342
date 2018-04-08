#include <stdio.h>
void foo(void);
void bar(void);
int main(int argc, char *argv[])
{
  foo();
}
void foo()
{
  printf("Hello ");
  bar();
}
void bar()
{
  printf("world!\n");
}
