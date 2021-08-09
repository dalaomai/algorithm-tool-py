/* test.i */
%module test 
%{
#include "test.h"
%}

class Test
{
public:
    int Hello(int, int);

private:
    int x;
    int y;
};