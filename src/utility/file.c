#include <stdio.h>
#include <stdlib.h>
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
  * Note that we don't to exit if the file doesn't exist
  * since we may only want to handle this.
  *
  * path: The file path as a character array
  * returns: The size of the file on disk
  */
long int file_size(char* path) {
  FILE* fp = fopen(path, "r");

  if (!file_exists(fp))
    return -1;

  fseek(fp, 0L, SEEK_END);
  // calculate the size of the file
  long int res = ftell(fp);
  rewind(fp);

  // closing the file
  fclose(fp);
  return res;
}

/**
  * Checks if a file is below a set size limit
  * path: The file path
  * size: The upper bound size limit
  * returns: True if the file is less than or equal to the upper bound and False otherwise
  */
bool under_limit(char* path, size_t size) {
  size_t filesize = file_size(path);
  bool result = (filesize <= size) ? true : false;
  return result;
}

/**
  * Read a file into a character array
  * ----------------------------------
  * path: A file path
  * returns: The file contents as a character array
  */
char* read_file(char* path) {

  FILE *fp = fopen(path, "rb");
  size_t filesize = file_size(path);

  /* Allocate a buffer for the file contents on the heap */
  void* buffer = malloc(filesize + 1);
  if (!buffer) {
    printf("Could not allocate buffer of size %ld\n", filesize + 1);
    exit(1);
  }

  char *contents = (char*) buffer;
  fread(contents, filesize, 1, fp);
  fclose(fp);
  contents[filesize] = 0;
  return contents;
}
