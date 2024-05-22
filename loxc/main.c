#include <stdio.h>
#include <stdlib.h>

static int hadError = 0;

void report(int line, char *where, char *message)
{
  printf("[line %i] Error %s: %s", line, where, message);
  hadError = 1;
}

void error(int line, char *message)
{
  report(line, "", message);
}

void run(char *source)
{
  printf("%s\n", source);
}

char *readFile(const char *path)
{
  FILE *file = fopen(path, "rb");
  if (file == NULL)
  {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (bytesRead < fileSize)
  {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

void runFile(const char *path)
{
  char *source = readFile(path);
  run(source);
  if (hadError)
    exit(65);
  free(source);
}

void runPrompt()
{
  char line[1024];
  for (;;)
  {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin))
    {
      printf("\n");
      break;
    }

    run(line);
    hadError = 0;
  }
}

int main(int argc, const char *argv[])
{
  if (argc == 1)
  {
    runPrompt();
  }
  else if (argc == 2)
  {
    runFile(argv[1]);
  }
  else
  {
    printf("Usage: ./main [script]\n");
    return 64;
  }
  return 0;
}