#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void freq_count(FILE *f, int *array) {
  int c;
  while((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      array[c]++;
    }
  }
}


void decrypt(FILE *f, int *array) {
  int idx_largest_count=0;
  int key;
  freq_count(f, array);
  for (int i=0; i<26; i++) {
    if (array[i] > array[idx_largest_count]) {
      idx_largest_count = i;
    }
  }
  if ((idx_largest_count) < ('e'-'a')) {
    key = idx_largest_count + 26 - ('e'-'a');
  }
  else {
    key = idx_largest_count - ('e'-'a');
  }
  printf("%d\n", key);
}

int main(int argc, char ** argv) {
  int char_array[26] = {0};
  if (argc != 2) {
    fprintf(stderr, "Usage: decrypt inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }

  decrypt(f, char_array);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
    
  return EXIT_SUCCESS;
}
