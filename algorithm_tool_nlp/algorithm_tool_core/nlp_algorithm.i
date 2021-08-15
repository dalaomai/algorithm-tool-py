/* nlp_algorithm.i */
%module nlp_algorithm 
%{
#include "nlp_algorithm.h"
%}

%include std_string.i
%inline %{
using namespace std;
%}

int LevenshteinDis(string s, int s_len, string t, int t_len);
int LevenshteinDP(string s, string t);