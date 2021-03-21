#include<stdio.h>

int max_number(int *a, int *b);

size_t maxSeq(int * array, size_t n) {
  int longest_seq = 0;
  int cur_max_seq = 0;
  int * cur_ptr;
  if (n > 0) {
    longest_seq = 1;
    cur_max_seq = 1;
    cur_ptr = &array[1];
    for (int i=1; i<n; i++) {
      if (* cur_ptr > *(cur_ptr-1)) {
	cur_max_seq += 1;
      }
      else {
	cur_max_seq = 1;
      }
      longest_seq = max_number(& longest_seq, & cur_max_seq);
      cur_ptr++;
    }
  }
  printf("longest sequence: %d\n", longest_seq);
  return longest_seq;
}


int max_number(int *a, int *b) {
  if (*a > *b) {
    return *a;
  }
  else {
    return *b;
  }
}
