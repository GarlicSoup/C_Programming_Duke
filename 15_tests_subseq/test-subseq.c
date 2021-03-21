#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t);

int main() {
  int test1[] = {-1, -2, -3, -4};
  int test2[] = {-2, -4, 5, 7, 3, 2};
  int test3[] = {-5, 2, 3, 4, 8, 1, 2, 3, 4};
  int test4[] = {-9, -7, -3, -1, 0, 4, 5, 2};
  int test5[] = {90, 90};
  int test6[] = {1, 1, 2, 3, 5, 5};
  int test7[] = {};
  int *array_ptr[] = {test1, test2, test3, test4, test5, test6, test7};
  int ans[] = {1, 3, 5, 5, 1, 4, 0};
  int test_lens[] = {4, 6, 9, 8, 2, 6, 0};

  for (int i=0; i<7; i++) {
    if (maxSeq(array_ptr[i],test_lens[i]) != ans[i]) {
	return EXIT_FAILURE;
      }
  }
  return EXIT_SUCCESS;
}
