#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int
main (int argc, char* argv[argc+1])
{
  if (argc < 3)
    {
      fprintf (stderr,
               "Usage: lgrep PATTERN FILE...\n"
               "Search for PATTERN in each FILE.\n"
               "PATTERN is literal string.\n"
               "Example: grep 'hello world' lgrep.c Makefile\n");
      return EXIT_FAILURE;
    }

  int ret = EXIT_SUCCESS;
  for (int i = 2; i < argc; i++)
    {
      FILE* instream = fopen (argv[i], "r");
      if (instream)
        {
          /* XXX: Very long line will fail? */
          char* buffer = 0;
          size_t n = 0;
          while (getline (&buffer, &n, instream) != -1)
            {
              if (strstr (buffer, argv[1]))
                fputs (buffer, stdout);
            }
          free (buffer);
          fclose (instream);
        }
      else
        {
          perror ("fopen");
          errno = 0;            /* reset error code */
          ret = EXIT_FAILURE;
        }
    }

  return ret;
}
