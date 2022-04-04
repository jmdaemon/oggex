#include <stdio.h>
#include <stdlib.h>

/* Executes a command, and prints the output of the command */
char* exec(const char* command, size_t size) {
  FILE *fp;
  char buffer[size];

  /* Open the command for reading. */
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    printf("%s", buffer);
  }

  /* close */
  pclose(fp);

  return 0;
}
