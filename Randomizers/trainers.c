#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include "../42-libft/libft.h"
#include "../Resources/pokemon.h"

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

char *is_monsno(char *line, char **encount, int index)
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
		if (ft_strnstr(tab[i], "MonsNo", ft_strlen(tab[i])) != NULL)
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
				tmp = ft_strjoin("     ", tmp);
				return (tmp);
			}
		}
		i++;
	}
	return (line);
}

char *fix_formno(char *line)
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
		if (ft_strnstr(tab[i], "FormNo", ft_strlen(tab[i])) != NULL)
		{
			//check if the value associated is NOT 0, which guarantees no write to unwanted lines
			if (ft_strncmp(tab[i + 2], "0", ft_strlen("0")) != 0)
			{
				int num = 0;
				tab[i + 2] = ft_itoa(num);
				printf("%d\n", num);
				//get tab size
				while(tab[j])
					j++;
				tmp = convertToLine(j, tab);
				tmp = ft_strjoin("     ", tmp);
				return (tmp);
			}
		}
		i++;
	}
	return (line);   
}

int main(int argc, char **argv)
{
    char const* const fileName = argv[1]; 
    FILE* file;
	char const *newfile = ft_strjoin(argv[1], "_randomised");
	FILE *new;
	char *buffer;
	char **tab = NULL;
	char **trainer_table;
	long lSize;
	int i = 0;
    int j = 1;

	srand((unsigned int)time(NULL)); //set random seed
	file = fopen(fileName, "rb"); 
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
	trainer_table = ft_split(buffer, '\n');
	free(buffer); //dont need it anymore

    printf("We're in boys\n");

    char *temp;
    while (trainer_table[i])
    {
        //temp = ft_strjoin("P", ft_itoa(j));
        //temp = ft_strjoin(temp, "MonsNo");
        if (ft_strnstr(trainer_table[i], "MonsNo", ft_strlen(trainer_table[i])) != NULL)
            temp = is_monsno(trainer_table[i], trainer_table, i);
        else if (ft_strnstr(trainer_table[i], "FormNo", ft_strlen(trainer_table[i])) != NULL)
            temp = fix_formno(trainer_table[i]);
		else
			temp = ft_strdup(trainer_table[i]);
		printf("%s\n", temp);
		fputs(temp, new);
		fputs("\n", new);
		free(temp);
		i++;
    }

    i = 0;
	while (trainer_table[i])
	{
		free(trainer_table[i]);
		i++;
	}
    free(trainer_table);
    fclose(file);
	fclose(new);
}

