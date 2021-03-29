#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->num_counts = 0;
  counts->counts = NULL;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  char const * input_name;
  if (name == NULL) {
    input_name = "<unknown>";
  }
  else {
    input_name = name;
  }
  for (size_t i=0; i<c->num_counts; i++) {
    if (!strcmp(c->counts[i]->name, input_name)) {
      c->counts[i]->count ++;
      return;
    }
  }
  
  c->counts = realloc(c->counts, (c->num_counts+1)* sizeof(*(c->counts)));
  c->counts[c->num_counts] = malloc(sizeof(*(c->counts[c->num_counts])));
  //c->counts[c->num_counts]->name = malloc((strlen(name) + 1)*sizeof(*(c->counts[c->num_counts]->name)));
  c->counts[c->num_counts]->name = input_name;
  c->counts[c->num_counts]->count = 1;
  c->num_counts++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  one_count_t * unknown = NULL;
  char * unk_ptr = NULL;
  for (size_t i=0; i<c->num_counts; i++) {
    unk_ptr = strstr(c->counts[i]->name, "<unknown>");
    if (unk_ptr == NULL) {
      fprintf(outFile, "%s: %zu\n", c->counts[i]->name, c->counts[i]->count);
    }
    else {
      unknown = c->counts[i];
    }
  }
  if (unknown != NULL) {
    fprintf(outFile, "%s: %zu", unknown->name, unknown->count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i=0; i<c->num_counts; i++) {
    //free(c->counts[i]->name);
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
}
