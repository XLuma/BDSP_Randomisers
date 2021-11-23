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

int pick_choice(int max)
{
	int min = 1; //min is always1, max is 3 or 10
    return rand() % ((max + 1) - min) + min;
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
				tab2 = ft_split(item_tab[i + 1], ' ');
				wazaNo = atoi(tab2[4]);
				return (wazaNo);
            }
        }
		i++;
    }
    return (wazaNo);
}

int	get_tm_type(int wazaNo, char **move_tab)
{
	//while loop till we find wazano, then we go two lines further to find the type
    int i = 0;
    char **tab = NULL;
    char **tab2 = NULL;
    int type = 0;

    while (move_tab[i])
    {
        if (ft_strnstr(move_tab[i], "wazaNo", ft_strlen(move_tab[i])) != NULL)
        {
            tab = ft_split(move_tab[i], ' ');
            if (wazaNo == atoi(tab[4]))
            {
				tab2 = ft_split(move_tab[i + 2], ' ');
				type = atoi(tab2[4]);
				return (type);
            }
        }
		i++;
    }
    return (type);
}

void new_compat(char **machine_tab, char **item_tab, char **move_tab, t_moninfo *mon)
{
    //tm's start at line 71110
    char **tab = NULL;
    char *tmp = NULL;
    int i = 0;
    int j = 0;
    int current_tm = 0;
    int index = 0;

    //parse machine data into tm struct
    int machine = 1;
    printf("hey\n");
    while (machine_tab[i] && index < 4)
    {
        tab = ft_split(machine_tab[i], ' ');
        if (machine == 1)
        {
            mon->machine1 = strtoul(tab[5], &tmp, 10);
            printf("%ld\n", mon->machine1);
            i++;
            index++;
        }
        if (machine == 2)
        {
            mon->machine2 = strtoul(tab[5], &tmp, 10);
            printf("%ld\n", mon->machine2);
            i++;
            index++;
        }
        if (machine == 3)
        {
            mon->machine3 = strtoul(tab[5], &tmp, 10);
            printf("%ld\n", mon->machine3);
            i++;
            index++;
        }
        if (machine == 4)
        {
            mon->machine4 = strtoul(tab[5], &tmp, 10);
            printf("%ld\n", mon->machine4);
            i++;
            index++;
        }
        machine++;
    }
    //all mon values are now set hopefully, now we loop through each damn tm, set the type and move num, and determine if we get a 90% or 33% chance
    //we also need to figure out how to change from machine1 to another depending on current tm
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
	//thats absolutely dirty but hey
    while (current_tm < 100)
    {
        if (current_tm >= 0 && current_tm <= 31)
        {
            mon->tm.num = get_tm_num(current_tm, item_tab, move_tab);
            mon->tm.type  = get_tm_type(mon->tm.num, move_tab);
			if (mon->tm.type == mon->type1 || mon->tm.type == mon->type2)
			{
				//probability of 90% to get a compatible tm
				if (pick_choice(10) != 10)
				{
					//set bit to 1
					mon->machine1 |= 1UL << counter1;
				}
				else
				{
					mon->machine1 &= ~(1UL << counter1);
				}
			}
			else
			{
				//probability of 33% of getting a compatible tm
				if (pick_choice(3) == 3)
				{
					mon->machine1 |= 1UL << counter1;
				}
				else
				{
					mon->machine1 &= ~(1UL << counter1);
				}
			}
			counter1++;
        }
        if (current_tm >= 32 && current_tm <= 63)
        {
            mon->tm.num = get_tm_num(current_tm, item_tab, move_tab);
            mon->tm.type  = get_tm_type(mon->tm.num, move_tab);
			if (mon->tm.type == mon->type1 || mon->tm.type == mon->type2)
			{
				//probability of 90% to get a compatible tm
				if (pick_choice(10) != 10)
				{
					//set bit to 1
					mon->machine2 |= 1UL << counter2;
				}
				else
				{
					mon->machine2 &= ~(1UL << counter2);
				}
			}
			else
			{
				//probability of 33% of getting a compatible tm
				if (pick_choice(3) == 3)
				{
					mon->machine2 |= 1UL << counter2;
				}
				else
				{
					mon->machine2 &= ~(1UL << counter2);
				}
			}
			counter2++;
        }
        if (current_tm >= 64 && current_tm <= 95)
        {
            mon->tm.num = get_tm_num(current_tm, item_tab, move_tab);
            mon->tm.type  = get_tm_type(mon->tm.num, move_tab);
			if (mon->tm.type == mon->type1 || mon->tm.type == mon->type2)
			{
				//probability of 90% to get a compatible tm
				if (pick_choice(10) != 10)
				{
					//set bit to 1
					mon->machine3 |= 1UL << counter3;
				}
				else
				{
					mon->machine3 &= ~(1UL << counter3);
				}
			}
			else
			{
				//probability of 33% of getting a compatible tm
				if (pick_choice(3) == 3)
				{
					mon->machine3 |= 1UL << counter3;
				}
				else
				{
					mon->machine3 &= ~(1UL << counter3);
				}
			}
			counter3++;
        }
        if (current_tm >= 96 && current_tm <= 99)
        {
            mon->tm.num = get_tm_num(current_tm, item_tab, move_tab);
            mon->tm.type  = get_tm_type(mon->tm.num, move_tab);
			if (mon->tm.type == mon->type1 || mon->tm.type == mon->type2)
			{
				//probability of 90% to get a compatible tm
				if (pick_choice(10) != 10)
				{
					//set bit to 1
					mon->machine4 |= 1UL << counter4;
				}
				else
				{
					mon->machine4 &= ~(1UL << counter4);
				}
			}
			else
			{
				//probability of 33% of getting a compatible tm
				if (pick_choice(3) == 3)
				{
					mon->machine4 |= 1UL << counter4;
				}
				else
				{
					mon->machine4 &= ~(1UL << counter4);
				}
			}
			counter4++;
		}
        current_tm++;
    }
    //printf("New compat1: %ld\n", mon->machine1);
    //printf("%ld\n", mon->machine2);
   // printf("%ld\n", mon->machine3);
   // printf("%ld\n", mon->machine4);
	//all 100 tm's have been assigned properly, technically we dont need to return anything I think ?
	//nvm I need to put back into tab_,machines the unsigned longs for writing
	//fuck it, void function and new function to create new strings lmao
}

char **new_tab_machine(char **tab_machine, t_moninfo *mon)
{
	int	i = 0;
	int j = 0;
	char **tmp = NULL;
	char **ret = NULL;
	char *line = NULL;
    int index = 0;

	ret = malloc(4);
    line = malloc(11);
	while (tab_machine[i] && index < 4)
	{
		tmp = ft_split(tab_machine[i], ' ');
        if (i == 0)
            tmp[5] = ft_strdup(ft_ultoa(mon->machine1, line, 10));
        if (i == 1)
            tmp[5] = ft_strdup(ft_ultoa(mon->machine2, line, 10));
        if (i == 2)
            tmp[5] = ft_strdup(ft_ultoa(mon->machine3, line, 10));
        if (i == 3)
            tmp[5] = ft_strdup(ft_ultoa(mon->machine4, line, 10));
		while(tmp[j])
			j++;
		ret[i] = ft_strdup(convertToLine(j, tmp));
        ret[i] = ft_strjoin("     ", ret[i]);
        printf("%s\n", ret[i]);
		i++;
        index++;
	}
	return (ret);
}

int	retrieve_type(char **personal_table, int current_index, int type)
{
	int type_mon = 0;
    char **tab = NULL;

	switch (type)
	{
	case 1:
        tab = ft_split(personal_table[current_index], ' ');
        type_mon = atoi(tab[4]);
		break;
	case 2:
        tab = ft_split(personal_table[current_index], ' ');
        type_mon = atoi(tab[4]);
		break;
	}
    return (type_mon);
}

int main(int argc, char **argv)
{
    printf("hi\n");
    //const char *filename = argv[1]; //personal table
    const char *filename = "PersonalTable-CAB-e4b0255ada6b8a0648ba9bd2680c1371-6925071152922426992_bak.txt";
    const char *newfile = ft_strjoin(argv[1], "_randomised"); //output
    //const char *itemFile = argv[2]; //item table
    const char *itemFile = "ItemTable-CAB-e4b0255ada6b8a0648ba9bd2680c1371-252928009371549925.txt";
    //const char *moveData = argv[3]; //move data table; for types
    const char *moveData = "WazaTable-CAB-e4b0255ada6b8a0648ba9bd2680c1371--8825204264973564398.txt";

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
    printf("opening files\n");
    file = fopen(filename, "rb");
    item = fopen(itemFile, "rb");
    move = fopen(moveData, "rb");
    new = fopen(newfile, "w");
    printf("files opened\n");
    fseek(file, 0L, SEEK_END);
    fseek(item, 0L, SEEK_END);
    fseek(move, 0L, SEEK_END);
    printf("read file sizes\n");
    personal_size = ftell(file);
    item_size = ftell(item);
    move_size = ftell(move);
    printf("got file sizes\n");
    rewind(file);
    rewind(move);
    rewind(item);

    //Parse all files in arrays
    printf("Allocating memory for tables\n");
    personal_tab = (char **)malloc(personal_size + 1);
    //item_tab = (char **)malloc((item_size * sizeof(char*)) + 1);
    item_tab = calloc(72119, sizeof(char *));
    move_tab = (char **)malloc(move_size + 1);
    printf("%ld\n", item_size);
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
    line = NULL;
    lenght = NULL;
    while (!feof(item))
    {
        getline(&line, &lenght, item);
        item_tab[i] = ft_strdup(line);
        i++;
    }
    //read moves
    i = 0;
    while (!feof(move))
    {
        getline(&line, &lenght, move);
        move_tab[i] = ft_strdup(line);
        i++;
    }
    printf("Randomising TM compatibility...\n");
    i = 0;
    while (personal_tab[i])
    {
        if (ft_strnstr(personal_tab[i], "type", ft_strlen(personal_tab[i])) != NULL)
        {
			if (ft_strnstr(personal_tab[i], "type1", ft_strlen(personal_tab[i])) != NULL)
        	{
            	mon.type1 = retrieve_type(personal_tab, i, 1);
       		}
			if (ft_strnstr(personal_tab[i], "type2", ft_strlen(personal_tab[i])) != NULL)
        	{
            	mon.type2 = retrieve_type(personal_tab, i, 2);
       		}
        }
        if (ft_strnstr(personal_tab[i], "machine", ft_strlen(personal_tab[i])) != NULL)
        {
            //Read machine1 to 4, put that in the struct, and pass all this so we assign new tm compats
            int counter = 0;
            int current = i;
            char **tab_machine = malloc(4);
            while (ft_strnstr(personal_tab[current], "machine", ft_strlen(personal_tab[current])) != NULL && counter < 4)
            {
                tab_machine[counter] = ft_strdup(personal_tab[current]);
                counter++;
                current++;
            }
            counter = 0;
            //magic happens here
            printf("hallo\n");
            new_compat(tab_machine, item_tab, move_tab, &mon);
			tab_machine = new_tab_machine(tab_machine, &mon);
			//write to file
			while (tab_machine[counter] && counter < 4)
			{
                printf("%s\n", tab_machine[counter]);
				fputs(tab_machine[counter], new);
				if (ft_strnstr(tab_machine[counter], "\n", ft_strlen(tab_machine[counter])) == NULL)
					fputc('\n', new);
				counter++;
			}
			free(tab_machine);
			i += 4;
        }
		else // Other lines.
        {
            fputs(ft_strdup(personal_tab[i]), new);
            i++;
        }
        printf("%d\n", i);
    }
	return 0;
}