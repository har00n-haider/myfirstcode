#include <stdio.h>

int main(){
  int y = 3;
  int x = 2;
  printf("x value is %i \n y value is %i \n ", x, y);
  printf("pointer to the x value is %p \n pointer to the y value is %p \n ", &x, &y);
  increment(&x,&y);
  printf("incremented x is %i and incremented and y is %i\n", x,y);
  return 0;
}

int increment(int *a, int *b){
  printf("Passed value of pointer to a is %p \n Passed value of pointer to b is %p \n",a,b );
  printf("Passed value of a is %i \n Passed value of b is %i \n",*a,*b );
  *a = *a + 1;
  *b = *b + 1;
  printf("Incremented value of a is %i \n Incremented value of b is %i \n",*a,*b );
}
