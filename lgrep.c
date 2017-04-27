#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MYLIMIT 16384

void
grep (char* pattern, FILE* stream)
{
  char* line = malloc (MYLIMIT + 1);
  if (line == NULL)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }

  /* XXX: Line longer than MYLIMIT will split */
  while (fgets (line, MYLIMIT + 1, stream) != NULL)
    {
      /* XXX: Use regular expression */
      /* XXX: Find all matches not just the first one */
      /* XXX: Colorized the matching part */
      if (strstr (line, pattern))
        fputs (line, stdout);
    }
  free (line);
}

int
main (int argc, char* argv[argc+1])
{
  if (argc == 1)                /* zero argument */
    {
      fprintf (stderr, "Usage: lgrep PATTERN [FILE]...\n");
      return EXIT_FAILURE;
    }

  if (argc == 2)                /* one argument */
    {
      grep (argv[1], stdin);
      return EXIT_SUCCESS;
    }

  for (int i = 2; i < argc; i++) /* two or more arguments */
    {
      /* XXX: Handle '-' as stdin */
      FILE* instream = fopen (argv[i], "r");
      if (instream)
        {
          grep (argv[1], instream);
          fclose (instream);
        }
      else
        {
          perror ("fopen");
          errno = 0;            /* reset error code */
        }
    }

  return EXIT_SUCCESS;
}
