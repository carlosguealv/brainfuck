#include <stdio.h>
#include <errno.h>

#define VERSION "v0.1a"
#define MEMORY_SIZE 30000
#define SOURCE_SIZE 10000

int memory[MEMORY_SIZE];
char source[SOURCE_SIZE];
char *src = source;
int *mem = memory;
int loop;

void execute()
{
  while(*src) {
    switch(*src)
    {
      case '>': *mem++; break;
      case '<': *mem--; break;
      case '+': ++*mem; break;
      case '-': --*mem; break;
      case '.': putc(*mem, stdout); break;
      case ',': *mem = getc(stdin); break;

      case '[':
        if(!*mem) {
          loop = 1;
          while(loop) {
            *src++;

            if(*src == '[') loop++;
            if(*src == ']') loop--;
          }
        }
        break;
      case ']':
        
        loop = 1;

        while(loop) {
          *src--;

          if(*src == '[') loop--;
          if(*src == ']') loop++;
        }

        *src--;
        break;
    }

    *src++;
  }
}

int main(int argc, char* argv[])
{
  if(argc == 1) {
    printf("\n Brainfuck interpreter %s by Carlos Guerrero\n", VERSION);
    printf("  1. Type or paste in brainfuck source code\n");
    printf("  2. Use Ctrl-D for code execution(linux)\n");
    printf("  3. Use ./brainfuck [filename] to execute source file\n");

    fread(source, 1, SOURCE_SIZE - 1, stdin);
    execute();
  } else if(argc == 2) {
    FILE *file = fopen(argv[1], "r");

    if(errno) {
      printf("File '%s' doesn't exist!\n", argv[1]);
      return 0;
    }

    fread(source, 1, SOURCE_SIZE, file);
    fclose(file);
    execute();
  }

  return 0;
}
