#include <stdio.h>
#include <stdbool.h>

/**
  * Check if a file exists
  * ----------------------
  * If the file is not null then it is valid.
  *
  * fp: The file path to check
  * returns: True if the file is not null, and false otherwise
  */
bool file_exists(FILE* fp) {
  if (fp == NULL) {
    printf("File Not Found!\n");
    return false;
  }
  return true;
}

/**
  * Returns the size of the file on disk
  * ------------------------------------
  * path: The file path as a character array
  * returns: The size of the file on disk
  */
long int filesize(char* path) {
  FILE* fp = fopen(path, "r");

  if (!file_exists(fp))
    return -1;

  fseek(fp, 0L, SEEK_END);
  // calculate the size of the file
  long int res = ftell(fp);

  // closing the file
  fclose(fp);
  return res;
}
