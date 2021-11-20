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

int new_mon;
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

int	pick_mon()
{
	int min = 1;
	int max = 493;
	return rand()%((max+1)-min) + min;
}

int pick_move(int min, int max)
{
    return rand()%((max+1)-min) + min;
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
		if (ft_strnstr(tab[i], "MonsNo", ft_strlen(tab[i])) != NULL)
		{
			//check if the value associated is NOT 0, which guarantees no write to unwanted lines
			if (ft_strncmp(tab[i + 2], "0", ft_strlen("0")) != 0)
			{
				int num = pick_mon();
                new_mon = num;
				tab[i + 2] = ft_itoa(num);
				//printf("%d\n", num);
				//get tab size
				while(tab[j])
					j++;
				tmp = convertToLine(j, tab);
				tmp = ft_strjoin("     ", tmp);
                //tmp = ft_strjoin(tmp, "\n");
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
				//printf("%d\n", num);
				//get tab size
				while(tab[j])
					j++;
				tmp = convertToLine(j, tab);
				tmp = ft_strjoin("     ", tmp);
               // tmp = ft_strjoin(tmp, "\n");
				return (tmp);
			}
		}
		i++;
	}
	return (line);   
}

char *find_mon(char **names)
{
    return (names[new_mon]);
}

int resolve_move(int move, char **movelist, char *line)
{
    int i;
    char **tab;

    tab = ft_split(line, '@');
    i = 0;
    while (movelist[i])
    {
        if (strcmp(ft_strjoin(movelist[i], " "), tab[0]) == 0)
            return i;
        i++;
    }
    return 0;
}
char *new_move(char *line, char **learnset, char **names, char **movelist)
{
    int i;
    int j;
    int len;
    char *tmp;
    char **tab;
    char *mon;
    int move_index;

    i = 0;
    j = 0;
    len = 0;
    tab = ft_split(line, ' ');

    while (tab[i])
    {
        if (ft_strnstr(tab[i], "Waza", ft_strlen(tab[i])) != NULL)
        {
            //check if move isnt empty
            if (ft_strncmp(tab[i + 2], "0", ft_strlen("0")) != 0)
            {
                mon = find_mon(names);
              //  printf("Mon index: %s\n", mon);
             //   sleep(1);
                j = 0;
                while (learnset[j])
                {
              //      printf("%s\n", learnset[j]);
                    if (ft_strnstr(learnset[j], mon, ft_strlen(learnset[j])) != NULL)
                    {
                      //  sleep(1);
                      //  printf("%s", learnset[j]);
                        int current = j;
                        int max = 0;
                        int move;
                        while (ft_strnstr(learnset[current], "end", ft_strlen(learnset[current])) == NULL)
                        {
                            current++;
                            max++;
                        }
                        move = pick_move(1, max);
                     //   printf("Chosen move: %d\n", move);
                        move_index = resolve_move(move, movelist, learnset[j + move]);
                     //   printf("Move resolved to: %d\n", move_index);
                        tab[i + 2] = ft_itoa(move_index);
                        while(tab[len])
                            len++;
                        tmp = convertToLine(len, tab);
				        tmp = ft_strjoin("     ", tmp);
                     //   tmp = ft_strjoin(tmp, "\n");
			        	return (tmp);
                    }
                    j++;
                }
            }
        }
        i++;
    }
    return (line);
}

int main(int argc, char **argv)
{
    char const* const fileName = argv[1];
    char const *movepoolFile = "Resources/learnsets.txt";
    char const *monName = "Resources/pokemon.txt";
    char const *moveName = "Resources/movelist.txt";
    char const *newfile = ft_strjoin(argv[1], "_randomised");
    FILE* file;
    FILE *movepool;
	FILE *new;
    FILE *monFile;
    FILE *moveFile;
	char *buffer;
	char **trTab = NULL;
	char **movepoolTab;
    char **monTab;
    char **moveTab;
	long lSize;
    long trSize;
    long monSize;
    long moveSize;
	int i = 0;
    int j = 1;
    new_mon = 0;

	srand((unsigned int)time(NULL)); //set random seed
	file = fopen(fileName, "rb");
    monFile = fopen(monName, "rb");
    movepool = fopen(movepoolFile, "rb");
    moveFile = fopen(moveName, "rb");
	new = fopen(newfile, "w");
	fseek(movepool, 0L, SEEK_END);
    fseek(file, 0L, SEEK_END);
    fseek(monFile, 0L, SEEK_END);
    fseek(moveFile, 0L, SEEK_END);
    moveSize = ftell(moveFile);
    monSize = ftell(monFile);
    trSize = ftell(file);
	lSize = ftell(movepool);
    rewind(moveFile);
	rewind(movepool);
    rewind(file);
    rewind(monFile);

	//Allocating the memory
	printf("Allocating mem for movepool\n");
    trTab = (char **)malloc((trSize * sizeof(char*)) + 1); //also allocating for trtab

    //This is kept for the movepoolfile
	buffer = malloc(lSize + 1);
	if( !buffer ) fclose(file),fputs("memory alloc fails",stderr),exit(1);
	printf("Reading moveset table\n");
	if( 1!=fread( buffer , lSize, 1, movepool) )
  		fclose(file),free(buffer),fputs("entire read fails",stderr),exit(1);

    movepoolTab = ft_split(buffer, '\n');
    free (buffer);

    buffer = malloc(monSize + 1);
    printf("Reading Pokemon table\n");
	if( 1!=fread( buffer , monSize, 1, monFile) )
  		fclose(file),free(buffer),fputs("entire read fails",stderr),exit(1);
    
    monTab = ft_split(buffer, '\n');
    free(buffer);

    printf("Reading movelist table\n");
    buffer = malloc(moveSize + 1);
	if( 1!=fread( buffer , moveSize, 1, moveFile) )
  		fclose(file),free(buffer),fputs("entire read fails",stderr),exit(1);
    
    moveTab = ft_split(buffer, '\n');
    free(buffer);


    //Read trainer file by line, put in tab
    char *line = NULL;
    long lenght;
    printf("Reading trainer table\n");
    while (!feof(file))
    {
        getline(&line, &lenght, file);
        trTab[i] = ft_strdup(line);
        i++;
    }

    //randomise
    printf("Randomising\n");
    char *temp = NULL;
    i = 0;
    while (trTab[i])
    {
        if (ft_strnstr(trTab[i], "MonsNo", ft_strlen(trTab[i])) != NULL)
        {
            temp = is_monsno(trTab[i]);
            fputs(temp, new);
            if (ft_strnstr(temp, "\n", ft_strlen(temp)) == NULL)
                fputc('\n', new);
            i++;
        }
        else if (ft_strnstr(trTab[i], "FormNo", ft_strlen(trTab[i])) != NULL)
        {
            temp = fix_formno(trTab[i]);
            fputs(temp, new);
            if (ft_strnstr(temp, "\n", ft_strlen(temp)) == NULL)
                fputc('\n', new);
            i++;
        }
        else if (ft_strnstr(trTab[i], "Waza", ft_strlen(trTab[i])) != NULL)
        {
            int counter = 0;
            char **tab_waza;
            int current = i;
            tab_waza = malloc(4);
            while (ft_strnstr(trTab[current], "Waza", ft_strlen(trTab[current])) != NULL && counter < 4)
            {
                tab_waza[counter] = ft_strdup(trTab[current]);
                counter++;
                current++;
            }
            counter = 0;
            while (tab_waza[counter] && counter < 4)
            {
                tab_waza[counter] = new_move(tab_waza[counter], movepoolTab, monTab, moveTab);
                counter++;
            }
            counter = 0;
            while (tab_waza[counter] && counter < 4)
            {

                fputs(tab_waza[counter], new);
                if (ft_strnstr(tab_waza[counter], "\n", ft_strlen(tab_waza[counter])) == NULL)
                    fputc('\n', new);
                counter++;
            }
            free(tab_waza);
            while (ft_strnstr(trTab[i], "Waza", ft_strlen(trTab[i])) != NULL)
            {
                i++;
            }
            
        }
		else
        {
			temp = ft_strdup(trTab[i]);
            fputs(temp, new);
            i++;
        }
    }
    fclose (file);
    fclose (movepool);
    fclose (new);
    fclose (moveFile);
    fclose (monFile);

    return 0;
}

