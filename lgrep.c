#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void
grep (char* pattern, FILE* instream)
{
  /* XXX: Very long line will fail? */
  char* buffer = 0;
  size_t n = 0;
  while (getline (&buffer, &n, instream) != -1)
    {
      /* XXX: Use regular expression */
      /* XXX: Find all matches not just the first one */
      /* XXX: Colorized the matching part */
      if (strstr (buffer, pattern))
        fputs (buffer, stdout);
    }
  free (buffer);
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
