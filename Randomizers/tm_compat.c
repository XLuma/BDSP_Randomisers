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

int    get_tm_num(int tmNum, char **item_tab, char **move_tab)
{
    //find the correct wazano for tmNum. in itemtable, machinenum are 1-100 so we add one to the current tmNum to find the wazano we want
    //tm's start at line 71110
    int machineNo = tmNum + 1;
    int i = 71110;
    char **tab = NULL;
    char **tab2 = NULL;
    int wazaNo = 0;

    while (item_tab[i])
    {
        if (ft_strnstr(item_tab[i], "machineNo", ft_strlen(item_tab[i])) != NULL)
        {
            tab = ft_split(item_tab[i], ' ');
            if (machineNo == atoi(tab[4]))
            {

            }
            
            return (wazaNo);
        }
    }
    return (wazaNo);
}

char **new_compat(char **machine_tab, char **item_tab, char **move_tab, t_moninfo *mon)
{
    //tm's start at line 71110
    char **tab = NULL;
    char *tmp = NULL;
    int i = 0;
    int j = 0;
    int current_tm = 0;

    //parse machine data into tm struct
    int machine = 1;
    while (machine_tab[i])
    {
        tab = ft_split(machine_tab[i], ' ');
        switch (machine)
        {
            case 1:
                mon->machine1 = strtoul(tab[5], &tmp, 10);
                break;
            case 2:
                mon->machine2 = strtoul(tab[5], &tmp, 10);
                break;
            case 3:
                mon->machine3 = strtoul(tab[5], &tmp, 10);
                break;
            case 4:
                mon->machine4 = strtoul(tab[5], &tmp, 10);
                break;
        }
        i++;
        machine++;
    }
    //all mon values are now set hopefully, now we loop through each damn tm, set the type and move num, and determine if we get a 90% or 33% chance
    //we also need to figure out how to change from machine1 to another depending on current tm
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    while (current_tm < 100)
    {
        if (current_tm >= 0 && current_tm <= 31)
        {
            mon->tm.num = get_tm_num(current_tm, item_tab);
            mon->tm.type  = get_tm_type(mon->tm.num, move_tab);

        }
        if (current_tm >= 32 && current_tm <= 63)
        {
            mon->tm.num = get_tm_num(current_tm, item_tab);
        }
        if (current_tm >= 64 && current_tm <= 95)
        {
            mon->tm.num = get_tm_num(current_tm, item_tab);
        }
        if (current_tm >= 96 && current_tm <= 99)
        {
            mon->tm.num = get_tm_num(current_tm, item_tab);
        }
        current_tm++;
    }
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
            char **tab_machine = malloc(4);

            while (ft_strnstr(personal_tab[current], "machine", ft_strlen(personal_tab[current])) != NULL && counter < 4)
            {
                tab_machine[counter] = ft_strdup(personal_tab[current]);
                counter++;
                current++;
            }
            counter = 0;
            //magic happens here
            tab_machine = new_compat(tab_machine, item_tab, move_tab, &mon);
        }
        i++;
    }
}