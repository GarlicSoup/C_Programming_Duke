#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * counts = createCounts();
  FILE * f = fopen(filename, "r");

  if (f == NULL) {
    perror("Could not open file!\n");
    return NULL;
  }
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    char * newline_p = strchr(line, '\n');
    if (newline_p != NULL) {
      *newline_p = '\0';
    }
    char * value = lookupValue(kvPairs, line);
    addCount(counts, value);
  }
  free(line);
  line = NULL;

  if (fclose(f) != 0) {
    perror("Could not close file!\n");
    return NULL;
  }
  
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 2) {
    fprintf(stderr, "Usage: this_program key_value_file lookup_file_1 lookup_file_2 ...");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);

 //count from 2 to argc (call the number you count i)
  for (size_t i=2; i<argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL) {
      perror("Error with the lookup_file");
      return EXIT_FAILURE;
    }
    //compute the output file name from argv[i] (call this outName)
    char * suffix_outName = ".counts";
    char * outName = malloc((strlen(argv[i]) + strlen(suffix_outName) + 1) * sizeof(*outName));
    strcpy(outName, argv[i]);
    strcat(outName, suffix_outName);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("Could not open file!\n");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      perror("Could not close file!\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
  freeKVs(kv);
  
  return EXIT_SUCCESS;
}
