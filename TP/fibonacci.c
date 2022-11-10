#include "fibonacci.h"

int fibo(int n){
    if(n == 0 || n == 1)
      return n;
    
    int fibonacci = fibo(n-1) + fibo(n-2);
    return fibonacci;
}