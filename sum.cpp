// Sums all numbers in array
// Jason Sun, 19 Feb 2013

int wain(int*, int);
void println(int);

// === Insert WLPP Program Here ===
int wain(int* a, int n) {
    int i = 0;
    int sum = 0;
    while (i != n) {
        sum = sum + *(a+i);
        i = i + 1;
    }
    return sum;
}

#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv) {
  int l, c;
  int* a;
  printf("Enter length of array: ");
  scanf("%d", &l);
  a = (int*) malloc(l*sizeof(int));
  for(int i = 0; i < l; i++) {
    printf("Enter value of array element %d: ", i);
    scanf("%d", a+i);
  }
  c = wain(a,l);
  printf("wain returned %d\n", c);
  return 0;
}
void println(int x){
   printf("%d\n",x);
}
