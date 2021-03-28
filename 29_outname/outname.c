#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {

  char name_extension[] = ".count";
  char * output_file_name = malloc((strlen(inputName)+strlen(name_extension)+1) * sizeof(output_file_name));
  strcpy(output_file_name, inputName);
  strcat(output_file_name, name_extension);
  return output_file_name;
}
