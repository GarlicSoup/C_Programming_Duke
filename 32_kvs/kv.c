#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include <assert.h>

kvpair_t * split_kv(char * kv_str) {

  char * ptr = strchr(kv_str, '=');
  if (ptr == NULL) {
    return NULL;
  }
  *ptr = '\0';
  ptr++;
  // Strip new line
  char * p = strchr(ptr, '\n');
  if (p != NULL) {
    *p = '\0';
  }
  // Allocate memory on Heap for pair
  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = kv_str;
  pair->value = ptr;
  return pair;
}

kvarray_t * read_split_kv(FILE * fname, kvarray_t * kv_pairs) {
  char * kv_str = NULL;
  size_t sz = 0;
  size_t num_pairs = kv_pairs->num_pairs;
  kvpair_t * pair = NULL; 
  while (getline(&kv_str, &sz, fname) >= 0) {
    kv_pairs->pairs = realloc(kv_pairs->pairs, (num_pairs+1)*sizeof(*(kv_pairs->pairs)));

    pair = split_kv(kv_str);
    if (pair == NULL) {
      perror("Received a string that was not key-value pair!\n");
      freeKVs(kv_pairs);
      return NULL;
    }
    
    kv_pairs->pairs[num_pairs] = pair;
    kv_str = NULL;
    num_pairs++;
  }
  pair=NULL;
  free(kv_str);
  kv_pairs->num_pairs = num_pairs;
  
  return kv_pairs;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f =fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file!\n");
    return NULL;
  }

  kvarray_t * kv_pairs = malloc(sizeof(*kv_pairs));
  kv_pairs->num_pairs = 0;
  kv_pairs->pairs = NULL;
  kv_pairs = read_split_kv(f, kv_pairs);

  if (fclose(f) != 0) {
    perror("Could not close the file");
    return NULL;
  }
  
  return kv_pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i=0; i<pairs->num_pairs; i++) {
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  char * key;
  char * value;
  for (size_t i=0; i<pairs->num_pairs; i++) {
    key = pairs->pairs[i]->key;
    value = pairs->pairs[i]->value;
    printf("key = '%s' value = '%s'\n", key, value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i=0; i<pairs->num_pairs; i++) {
    if (!strcmp(pairs->pairs[i]->key, key)) {
      return pairs->pairs[i]->key;
    }
  }
  return NULL;
}
