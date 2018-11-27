#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int fibonacciSequence(int number)
{
  if(number <= 1)
    return number;
  return fibonacciSequence(number-1) + fibonacciSequence(number-2);
}

int main(int argc, char *argv[])
{
  //usage validation:                                                                                     
  if(argc != 2){
    printf("USAGE: ./a.out NUMBER_OF_DIGITS");
    return -1;
  }
                                                                             
  int number = atoi(argv[1]); 
  printf("%d", fibonacciSequence(number));
  

  return 0;
}
