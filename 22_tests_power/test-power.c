#include<stdio.h>
#include<stdlib.h>


unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(1, 0, 1);
  run_check(0, 1, 0);
  run_check(5, 1, 5);
  run_check(5, 0, 1);
  run_check(3, 7, 2187);
  run_check(6, 5, 7776);
  run_check(2*3 , 2, 36);
  run_check(1, 5, 1);
  run_check(0, 0, 1);
  run_check(0, 5, 0);
  run_check(2, 10, 1024);
  run_check(10, 2, 100);
  run_check(10, 5, 100000);
  
  return EXIT_SUCCESS;
}
