#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include "../42-libft/libft.h"
#include "../Resources/items.h"

typedef struct s_scriptFieldItem{
	int argtype; //if argtype is 0, we want to print it instead, maybe even skip cmd too
	int cmd; //if its not 187, dont do shit
	int data1; //item number
	int data2; //amount
} t_scriptFieldItem;

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

int check_pick(int pick)
{
	if (pick > ITEM_RAZOR_FANG || (pick >= ITEM_FIGY_BERRY && pick <= ITEM_ROWAP_BERRY) || (pick >= ITEM_GRASS_MAIL && pick <= ITEM_BRICK_MAIL) || pick == ITEM_ODD_KEYSTONE || (pick >= 113 && pick <= 134) || pick == ITEM_LIGHT_BALL || pick == ITEM_ORAN_BERRY || pick == ITEM_SHOAL_SALT || pick == ITEM_SHOAL_SHELL || (pick >= ITEM_GROWTH_MULCH && pick <= ITEM_GOOEY_MULCH) || (pick >= ITEM_LUCKY_PUNCH && pick <= ITEM_YELLOW_SCARF))
	{
		return 1;
	}
	return 0;
}

int pick_choice(void)
{
	int min = 1; //masterball as min, i guess the item right before an tm ?
	int max = 327;
	int pick;

    pick = rand()%((max+1)-min) + min;
	while (check_pick(pick) != 0)
	{
		pick = rand()%((max+1)-min) + min;
	}
	return (pick);
}

char	*call_python(char *mode, char *number)
{
	FILE *cmd;
	char *result = calloc(11, sizeof(char));

	char *tmp = ft_strjoin("python2 Resources/byteseq.py", mode);
	tmp = ft_strjoin(tmp, number);
	cmd = popen(tmp, "r");
	fread( result , 11, 1, cmd);
	pclose(cmd);
	return (result);
}

int	get_argtype(char *line)
{
	char **tab = NULL;
	int	argType = 0;
	tab = ft_split(line, ' ');
	return 0;
}

char *new_item(char *line)
{
	int i;
	int j;
	char **tab;
	char *ret;
	char *tmp;
	int item;

	i = 0;
	j = 0;
	tab = NULL;
	ret = NULL;
	tab = ft_split(line, ' ');
	while (tab[i])
	{
		if (ft_strnstr(tab[i], "data", ft_strlen(tab[i])) != NULL && ft_strnstr(tab[i - 1], "int", ft_strlen(tab[i - 1])) != NULL)
		{
			if (ft_strlen(tab[i + 2]) > 9 && ft_strnstr(tab[i + 2], "1065353216", ft_strlen("1065353216")) == NULL)
			{
				item = pick_choice();
				tmp = ft_strjoin(ft_itoa(item), ".0");
				tmp = ft_strdup(call_python(" encode ", tmp));
				printf("New encoded: %s\n", tmp);
				tab[i + 2] = ft_strdup(tmp);
				while (tab[j])
					j++;
				ret = convertToLine(j, tab);
				ret = ft_strjoin("             ", ret);
				return (ret);
			}
		}
		i++;
	}
	return (line);
}

int main(int argc, char **argv)
{
	const char *filename = argv[1]; //fld_item.txt for script
	const char *newfile =  ft_strjoin(argv[1], "_randomised");

	FILE *file;
	FILE *new;

	long fileSize;

	char *buffer;
	char **scriptTab;

	int i;
	int j;
	long lenght;

	t_scriptFieldItem script;

	srand((unsigned int)time(NULL)); //set random seed
	file = fopen(filename, "rb");
	new = fopen(newfile, "w");
	fseek(file, 0L, SEEK_END);
	fileSize = ftell(file);
	rewind(file);

	scriptTab = (char **)malloc((fileSize * sizeof(char *)) + 1);
	buffer = NULL;
	i = 0;
	lenght = 0;
	while (!feof(file))
    {
        getline(&buffer, &lenght, file);
        scriptTab[i] = ft_strdup(buffer);
        i++;
    }

	printf("Randomizing field items...\n");
	i = 0;
	char *tmp = NULL;
	while (scriptTab[i])
	{
		 //for each Label, the first argtype is 11 indexes later
		 //first one is command, second is item, third is amount.
		 //debate wheter we do 1 to 3 randomly
		 //anaylyzing the label is a method. if the string is longer than 15 charcaters, it might be a script
		 if (ft_strnstr(scriptTab[i], "data", ft_strlen(scriptTab[i])) != NULL)
		 {
			tmp = new_item(scriptTab[i]);
			fputs(tmp, new);
			if (ft_strnstr(tmp, "\n", ft_strlen(tmp)) == NULL)
                fputc('\n', new);
			i++;
		 }
		 else
		{
			tmp = ft_strdup(scriptTab[i]);
            fputs(tmp, new);
			i++;
		}
	}
	fclose(file);
	fclose(new);
	free(scriptTab);
	return 0;
}