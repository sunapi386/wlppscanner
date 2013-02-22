// Basically a gcd.cpp program, with constraints
// Jason Sun, 19 Feb 2013

int wain(int, int);
void println(int);

// === Insert WLPP Program Here ===
int wain(int a, int b) {
    int c = 0;
    if (b == 0) {
    } else {
        while (b != 0) {
            c = b;
            b = a % b;
            a = c;
        }
    }
    return a;
}

#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv) {
  int a,b,c;
  printf("Enter first integer: ");
  scanf("%d", &a);
  printf("Enter second integer: ");
  scanf("%d", &b);
  c = wain(a,b);
  printf("wain returned %d\n", c);
  return 0;
}
void println(int x){
   printf("%d\n",x);
}
