#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include "42-libft/libft.h"

char	*strip_nl(char *line)
{
	int i = 0;
	int len = ft_strlen(line);
	char *ret;

	while (i < len)
	{
		if (line[i] == '\n')
		{
			return ("1");
		}
		i++;
	}
	return (line);
}

int r() { 
  int s = (214013*s+2531011); 
  return (s>>16)&0x7FFF; 
} 

int	pick_mon()
{
	int min = 1;
	int max = 493;
	return rand()%((max+1)-min) + min;
}

char *convertToLine(int n, char **input) {
  /* compute the needed size,
     of course can also use malloc then realloc to avoid that */
  int size = 0;
  int i;

  for (i = 0; i != n; ++i)
    size += strlen(input[i]) + 1;

  /* copy the strings */
  char * string = (char*)malloc(size); /* sizeof(char) is 1 by definition */
  char * p = string;

  for (i = 0; i != n; ++i) 
  {
	  strcpy(p, input[i]);
	  p += strlen(p);
	  *p++ = ' ';
  }
  p[-1] = 0;

  return string;
}

char *is_monsno(char *line)
{
	char **tab;
	int 	i;
	int j;
	char	*tmp;
		
	//Analyze wheter we are a monsno line
	tab = ft_split(line, ' ');
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "monsNo", ft_strlen("monsNo")) == 0)
		{
			//check if the value associated is NOT 0, which guarantees no write to unwanted lines
			if (ft_strncmp(tab[i + 2], "0", ft_strlen("0")) != 0)
			{
				int num = pick_mon();
				tab[i + 2] = ft_itoa(num);
				printf("%d\n", num);
				//get tab size
				while(tab[j])
					j++;
				tmp = convertToLine(j, tab);
				return (tmp);
			}
		}
		i++;
	}
	return (line);
}

int main(int argc, char* argv[])
{
    char const* const fileName = argv[1]; /* should check that argc > 1 */
    FILE* file;/* should check the result */
	char const *newfile = ft_strjoin(argv[1], "_randomised");
	FILE *new;
	char *buffer;
    char line[256];
	char **tab = NULL;
	char **encount_tables;
	long lSize;
	int i = 0;

	srand((unsigned int)time(NULL)); //set random seed
	file = fopen(fileName, "rb"); /* should check the result */
	new = fopen(newfile, "w");
	fseek(file, 0L, SEEK_END);
	lSize = ftell(file);
	rewind(file);

	//Allocating the memory
	printf("Allocating mem\n");
	buffer = calloc(1, lSize +1);
	if( !buffer ) fclose(file),fputs("memory alloc fails",stderr),exit(1);

	/* copy the file into the buffer */
	printf("Reading encounter table\n");
	if( 1!=fread( buffer , lSize, 1 , file) )
  		fclose(file),free(buffer),fputs("entire read fails",stderr),exit(1);


	//Split the buffer in multiple lines, for better parsing
	encount_tables = ft_split(buffer, '\n');
	free(buffer); //dont need it anymore

	/*
	Ok apes, so here we have an array containing every god damn string. We need to figure out the lines to write.
	Down here is code that can already do that. Find the lines that contains monsno.
	We need to figure out if the number is 0, in which case we should do either nothing OR write a 0 again.
	How do we do that ?
	First solution:

	A function that takes two parameters: A line (that contains monsNo), and the new pokemon number.
	We: Split the line in sections, and verify if the last entry is a 0. If it is, we cancel and continue on the next line.
	If it is NOT a 0, we do line[i] = ft_itoa(number) which will change the number to a new one
	And then we join the string together by using spaces all okay. I need to make sure we dont cut the tabs or whatever.

	we kn
	*/

	printf("We're in boys\n");
	char *temp;
    while (encount_tables[i])
	{
		if (ft_strnstr(encount_tables[i], "monsNo", ft_strlen(encount_tables[i])) != NULL)
			temp = is_monsno(encount_tables[i]);
		else
			temp = ft_strdup(encount_tables[i]);
		printf("%s\n", temp);
		fputs(temp, new);
		fputs("\n", new);
		free(temp);
		i++;
	}
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */
	i = 0;
	while (encount_tables[i])
	{
		free(encount_tables[i]);
		i++;
	}
    fclose(file);
	fclose(new);

    return 0;
}