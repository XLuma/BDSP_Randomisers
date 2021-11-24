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
	if (pick > ITEM_EXPLORER_KIT || (pick >= ITEM_FIGY_BERRY && pick <= ITEM_ROWAP_BERRY) || (pick >= ITEM_GRASS_MAIL && pick <= ITEM_BRICK_MAIL) || pick == ITEM_ODD_KEYSTONE || (pick >= 113 && pick <= 134) || pick == ITEM_LIGHT_BALL || pick == ITEM_ORAN_BERRY || pick == ITEM_SHOAL_SALT || pick == ITEM_SHOAL_SHELL || (pick >= ITEM_GROWTH_MULCH && pick <= ITEM_GOOEY_MULCH) || (pick >= ITEM_LUCKY_PUNCH && pick <= ITEM_YELLOW_SCARF))
	{
		return 1;
	}
	return 0;
}

int pick_choice(void)
{
	int min = 1; //masterball as min, i guess the item right before an tm ?
	int max = 427;
	int pick;

    pick = rand()%((max+1)-min) + min;
	while (check_pick(pick) != 0)
	{
		pick = rand()%((max+1)-min) + min;
	}
	return (pick);
}

char *new_item(char *line)
{
	int i;
	int j;
	int item;
	char **tab;
	char *tmp;

	i = 0;
	j = 0;
	tab = ft_split(line, ' ');
	tmp = NULL;
	while (tab[i])
	{
		if (ft_strnstr(tab[i], "ItemNo", ft_strlen(tab[i])) != NULL)
		{
			item = pick_choice();
			tab[i + 2] = ft_itoa(item);
			while (tab[j])
				j++;
			tmp = convertToLine(j, tab);
			tmp = ft_strjoin("     ", tmp);
			return (tmp);
		}
		i++;
	}
	return (line);
}

int main(int argc, char **argv)
{
	const char *filename = argv[1];
	const char *newfile = ft_strjoin(argv[1], "_randomised");

	FILE *file;
	FILE *new;

	long fileSize;

	char *buffer;
	char **shopTab;

	int i;
	int j;
	long lenght;

	srand((unsigned int)time(NULL)); //set random seed
	file = fopen(filename, "rb");
	new = fopen(newfile, "w");
	fseek(file, 0L, SEEK_END);
	fileSize = ftell(file);
	rewind(file);

	shopTab = (char **)malloc((fileSize * sizeof(char *)) + 1);
	buffer = NULL;
	i = 0;
	lenght = 0;

	while (!feof(file))
    {
        getline(&buffer, &lenght, file);
        shopTab[i] = ft_strdup(buffer);
        i++;
    }

	printf("Randomizing shops...\n");
	i = 0;
	char *tmp = NULL;
	while (shopTab[i])
	{
		if (ft_strnstr(shopTab[i], "ItemNo", ft_strlen(shopTab[i])) != NULL && ft_strnstr(shopTab[i - 1], "SheetFixedShop data", ft_strlen(shopTab[i - 1])) != NULL)
		{
			//if we here, its a fixed shop so we randomise, otherwise just output as normal
			tmp = new_item(shopTab[i]);
			fputs(tmp, new);
			if (ft_strnstr(tmp, "\n", ft_strlen(tmp)) == NULL)
                fputc('\n', new);
			i++;
		}
		else
		{
			tmp = ft_strdup(shopTab[i]);
            fputs(tmp, new);
			i++;
		}
	}
	fclose(file);
	fclose(new);
	free(shopTab);
	printf("Done!\n");
	return 0;
}