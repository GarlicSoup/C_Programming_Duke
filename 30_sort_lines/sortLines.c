#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** read_data(FILE * stream, char ** line_array, size_t * line_count) {
  // This return number of lines read from the input file
  char * cur_line = NULL;
  size_t sz = 0;
  size_t line_num = 0;
  while (getline(&cur_line, &sz, stream) >= 0) {
    line_array = realloc(line_array, (line_num+1) *sizeof(*line_array));
    line_array[line_num] = cur_line;
    cur_line = NULL;
    line_num++;
  }
  free(cur_line);
  (*line_count) = line_num;
  return line_array;
}

void print_lines(char ** str_array, size_t line_num) {
  // print lines and free lines
  for (size_t i=0; i<line_num; i++) {
    printf("%s", str_array[i]);
    free(str_array[i]);
  }
  // free the string pointer container
  if (str_array != NULL) {
    free(str_array);
  }
}

int main(int argc, char ** argv) {
  char ** line_array = NULL;
  size_t line_num = 0;
  
  if (argc == 1) {
    line_array = read_data(stdin, line_array, &line_num);
    sortData(line_array, line_num);
    print_lines(line_array, line_num);
    line_array = NULL;
  }
  else if (argc > 1) {
    for (size_t i=1; i<argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
	perror("Could not open the file!\n");
	return EXIT_FAILURE;
      }
      line_num = 0;
      line_array = read_data(f, line_array, &line_num);
      sortData(line_array, line_num);
      print_lines(line_array, line_num);

      line_array = NULL;
      if (fclose(f) != 0) {
	perror("Failed to close the input file!\n");
	return EXIT_FAILURE;
      }
    }
  }
  
  return EXIT_SUCCESS;
}
