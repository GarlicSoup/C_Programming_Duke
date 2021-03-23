#include<stdio.h>

unsigned power_helper(unsigned x, unsigned y, unsigned ans) {
  if (x==0 && y==0) {
    return 1;
  }
  if (x==0) {
    return 0;
  }
  if (y <=0) {
    return ans;
  }
  return power_helper(x, y-1, ans*x);
}

unsigned power(unsigned x, unsigned y) {
  return power_helper(x, y, 1);
}
