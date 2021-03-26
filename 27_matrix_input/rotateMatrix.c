#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_value_matrix(FILE * f, char matrix[][10]) {
  int line_size = 12;
  char line[line_size];
  int char_count =0;
  int matrix_row = 0;
  while (fgets(line, line_size, f) != NULL) {
    char_count =0;
    
    if (strchr(line, '\n') == NULL) {
      fprintf(stderr, "Line has more than 10 characters!\n");
      exit(EXIT_FAILURE);
    }
    for (char_count=0; char_count<line_size; char_count++) {
      if (line[char_count] != '\n') {
	matrix[matrix_row][char_count] = line[char_count];
      }
      else {
	break;
      }
    }
    if (char_count != 10) {
      fprintf(stderr, "Line has %d character(s)!\n", char_count);
      //fprintf(stderr, "Line has less than 10 characters!\n");
      exit(EXIT_FAILURE);
    }
    matrix_row++;
  }
}

void rotate(char matrix[][10]) {
  int len = 10;
  int temp;
  for (int i=0; i<len/2; i++) {
    for (int j=i; j<len-i-1; j++) {
      temp = matrix[i][j];
      matrix[i][j] = matrix[len-j-1][i];
      matrix[len-j-1][i] = matrix[len-i-1][len-j-1];
      matrix[len-i-1][len-j-1] = matrix[j][len-i-1];
      matrix[j][len-i-1] = temp;
    }
  }
}

void print_matrix(char matrix[][10]) {
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      fprintf(stdout,"%c", matrix[i][j]);
    }
    fprintf(stdout,"\n");
  }
  return;
}


int main(int argc, char ** argv) {
  char matrix[10][10];

  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr,"Could not open file!\n");
    return EXIT_FAILURE;
  }
  
  get_value_matrix(f, matrix);
  //printf("original matrix:\n");
  //print_matrix(matrix);
  rotate(matrix);
  //printf("after being rotated:\n");
  print_matrix(matrix);
  
  if (fclose(f) != 0) {
    fprintf(stderr,"Failed to close the input file!\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
