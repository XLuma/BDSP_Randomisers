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
#include "../Resources/poketypes.h"

typedef struct s_tminfo{
    int num;
    int type;
} t_tminfo;

typedef struct s_moninfo{
    int type1;
    int type2;
    unsigned int machine1;
    unsigned int machine2;
    unsigned int machine3;
    unsigned int machine4;
} t_moninfo;


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

int pick_choice(void)
{
    //Set the TM or not
    return rand() % 2;
}


//tm data in itemdata starts at offset 0x1E5248
int main(int argc, char **argv)
{
    const char *filename = argv[1]; //personal table
    const char *newfile = ft_strjoin(argv[1], "_randomised"); //output
    const char *itemFile = argv[2]; //item table
    const char *moveData = argv[3]; //move data table; for types

    FILE *file;
    FILE *new;
    FILE *item;
    FILE *move;

    char *line = NULL;
    char *buffer = NULL;

    char **personal_tab = NULL;
    char **item_tab = NULL;
    char **move_tab = NULL;

    long personal_size;
    long item_size;
    long move_size;

    t_moninfo mon;
    t_tminfo tms;

    int i;
    int j;

    srand((unsigned int)time(NULL)); //set random seed

    file = fopen(filename, "rb");
    item = fopen(itemFile, "rb");
    move = fopen(moveData, "rb");
    new = fopen(newfile, "w");

    fseek(file, 0L, SEEK_END);
    fseek(item, 0L, SEEK_END);
    fseek(move, 0L, SEEK_END);

    personal_size = ftell(file);
    item_size = ftell(item);
    move_size = ftell(move);

    rewind(file);
    rewind(move);
    rewind(item);

    //Parse all files in arrays
    printf("Allocating memory for tables\n");
    personal_tab = (char **)malloc(personal_size + 1);
    item_size = (char **)malloc(item_size + 1);
    move_size = (char **)malloc(move_size + 1);

    //read personal
    long lenght;
    i = 0;
    printf("Reading all files\n");
    while (!feof(file))
    {
        getline(&line, &lenght, file);
        personal_tab[i] = ft_strdup(line);
        i++;
    }
    //read item
    i = 0;
    while (!feof(item))
    {
        getline(&line, &lenght, file);
        item_tab[i] = ft_strdup(line);
        i++;
    }
    //read moves
    i = 0;
    while (!feof(move))
    {
        getline(&line, &lenght, file);
        move_tab[i] = ft_strdup(line);
        i++;
    }

    printf("Randomising TM compatibility...\n");
    i = 0;
    while (personal_tab[i])
    {
        if (ft_strnstr(personal_tab[i], "type", ft_strlen(personal_tab[i])) != NULL)
        {
            mon.type1 = retrieve_type(personal_tab[i]);
            mon.type2 = retrieve_type(personal_tab[i + 1]);
            i++;
        }
        if (ft_strnstr(personal_tab[i], "machine", ft_strlen(personal_tab[i])) != NULL)
        {
            //Read machine1 to 4, put that in the struct, and pass all this so we assign new tm compats
            int counter = 0;
            int current = i;
        }
        i++;
    }
}